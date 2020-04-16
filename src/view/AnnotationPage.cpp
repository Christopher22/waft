//
// Created by christopher on 25.02.2020.
//

#include "AnnotationPage.h"
#include "AnnotationWidget.h"
#include "util/AspectRatioWidget.h"

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QAbstractButton>
#include <QCheckBox>

#include <limits>

namespace waft::view {

AnnotationPage::AnnotationPage(const model::Sample &sample, QWidget *parent)
	: QWizardPage(parent),
	  annotation_widget_(new AnnotationWidget(sample, this)),
	  next_id_(std::numeric_limits<int>::min()) {
  this->setTitle(tr("Annotation of '%1'").arg(sample.file().fileName()));
  this->setSubTitle(tr(
	  "Please annotate the pupil in the following frame. Click anywhere in the image to set the center of the ellipsis. Use your mouse wheel to rotate. Using %1 mouse wheel will scale the mayor axis, while utilize %2 mouse wheel will scale the minor one.")
						.arg(QKeySequence(Qt::SHIFT).toString(QKeySequence::NativeText),
							 QKeySequence(Qt::CTRL).toString(QKeySequence::NativeText)));

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(new util::AspectRatioWidget(annotation_widget_, this));
  this->setLayout(layout);
}

void AnnotationPage::initializePage() {
  QWizardPage::initializePage();

  // Use original id only if nothing different is given.
  if (next_id_ == std::numeric_limits<int>::min()) {
	next_id_ = QWizardPage::nextId();
  }

  // There is no way detecting the page was accessed using a back button. Listen for id change.
  QObject::connect(this->wizard(), &QWizard::currentIdChanged, this, [&](int id) {
	if (this == this->wizard()->page(id)) {
	  this->_prepare();
	}
  });

  // Prepare the check box on the first time
  this->_prepare();
}

int AnnotationPage::nextId() const {
  return next_id_;
}

void AnnotationPage::setNextId(int id) {
  next_id_ = id;
  this->setFinalPage(next_id_ == -1);
}

const model::Sample &AnnotationPage::sample() const {
  return annotation_widget_->sample();
}

void AnnotationPage::cleanupPage() {
  this->_cleanUp();
  QWizardPage::cleanupPage();
}

bool AnnotationPage::validatePage() {
  this->_cleanUp();
  return QWizardPage::validatePage();
}

QCheckBox *AnnotationPage::checkbox() noexcept {
  return qobject_cast<QCheckBox *>(this->wizard()->button(QWizard::CustomButton2));;
}

void AnnotationPage::_cleanUp() {
  auto *checkbox = this->checkbox();
  QObject::disconnect(checkbox, nullptr, this, nullptr);
  checkbox->setVisible(false);
}

void AnnotationPage::_prepare() {
  auto *checkbox = this->checkbox();
  checkbox->setChecked(this->sample().isMeaningful());
  QObject::connect(checkbox, &QCheckBox::stateChanged, this, [&](int state) {
	annotation_widget_->sample().setMeaningful(state == Qt::Checked);
	annotation_widget_->update();
  });
  checkbox->setVisible(true);
}

}