//
// Created by christopher on 04.03.2020.
//

#include "MultiInput.h"
#include <QButtonGroup>
#include <QFormLayout>
#include <QRadioButton>

namespace waft::view::inputs {

MultiInput::MultiInput(std::initializer_list<Input *> inputs, QWidget *parent)
	: Input(parent), inputs_(inputs.size()), buttons_(new QButtonGroup(this)), current_id_(-1) {
  Q_ASSERT(inputs.size() > 0);

  auto *layout = new QFormLayout(this);
  int button_index = 0;
  for (auto *input: inputs) {
	input->setParent(this);
	input->setEnabled(false);
	inputs_[button_index] = input;

	auto *button = new QRadioButton(input->inputName(), this);
	buttons_->addButton(button, button_index);
	layout->addRow(button, input);

	++button_index;
  }

  QObject::connect(buttons_,
				   qOverload<int, bool>(&QButtonGroup::buttonToggled),
				   this,
				   [this](int id, bool button_toggled) {
					 if (button_toggled) {
					   this->_setCurrentInput(id);
					 }
				   });

  this->_setCurrentInput(0);
  this->setLayout(layout);
}

bool MultiInput::isReady() const {
  return inputs_[current_id_]->isReady();
}

model::Samples *MultiInput::samples() {
  return inputs_[current_id_]->samples();
}

void MultiInput::_setCurrentInput(int next_index) {
  Q_ASSERT(next_index >= 0 && inputs_.size() > next_index);
  if (next_index == current_id_) {
	return;
  } else if (current_id_ == -1) {
	// This is called during construction of the widget
	current_id_ = 0;
  }

  auto *old_input = inputs_[current_id_];
  auto *new_input = inputs_[next_index];

  old_input->setEnabled(false);
  QObject::disconnect(old_input, nullptr, this, nullptr);
  const bool availability_changed = old_input->isReady() != new_input->isReady();

  current_id_ = next_index;
  QObject::connect(new_input, &Input::imagesChanged, this, [this] {
	emit this->imagesChanged();
  });
  QObject::connect(new_input, &Input::imageAvailabilityChanged, this, [this] {
	emit this->imageAvailabilityChanged();
  });

  // Ensure button is checked (i.e. during construction)
  if (!buttons_->button(next_index)->isChecked()) {
	buttons_->button(next_index)->setChecked(true);
  }
  new_input->setEnabled(true);

  // Raise the appropriate signals
  if (availability_changed) {
	emit this->imageAvailabilityChanged();
  }
  emit this->imagesChanged();
}

QString MultiInput::inputName() const {
  return tr("Choice of inputs: ");
}

}