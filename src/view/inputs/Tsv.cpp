//
// Created by christopher on 04.03.2020.
//

#include "Tsv.h"
#include "../../model/Samples.h"
#include "../../model/samples/SavedAnnotations.h"
#include "../util/FileSelector.h"

#include <QVBoxLayout>

namespace waft::view::inputs {

Tsv::Tsv(QWidget *parent)
	: Input(parent), selector_(new util::FileSelector(tr("Please select the existing annotations"),
													  tr("Annotations (*.tsv)"),
													  false,
													  QString(),
													  this)) {

  QObject::connect(selector_, &util::FileSelector::pathSelected, this, [this](const QString &) {
	emit this->imagesChanged();
	emit this->imageAvailabilityChanged();
  });

  auto *layout = new QVBoxLayout();
  layout->addWidget(selector_);
  this->setLayout(layout);
}

model::Samples *Tsv::samples() {
  QString path = selector_->path();
  if (path.isEmpty()) {
	return nullptr;
  }
  return new model::samples::SavedAnnotations(path, nullptr);
}

bool Tsv::isReady() const {
  return static_cast<bool>(*selector_);
}

QString Tsv::inputName() const {
  return tr("Existing annotations: ");
}
}