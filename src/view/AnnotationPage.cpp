//
// Created by christopher on 25.02.2020.
//

#include "AnnotationPage.h"
#include "AnnotationWidget.h"
#include "util/AspectRatioWidget.h"

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>

#include <limits>

namespace waft::view {

AnnotationPage::AnnotationPage(const model::Sample &sample, QWidget *parent)
	: QWizardPage(parent),
	  sample_(sample),
	  annotation_widget_(new util::AspectRatioWidget(new AnnotationWidget(sample, this), this)),
	  next_id_(std::numeric_limits<int>::min()) {
  this->setTitle(tr("Annotation of '%1'").arg(sample.file().fileName()));
  this->setSubTitle(tr(
	  "Please annotate the pupil in the following frame. Click anywhere in the image to set the center of the ellipsis. Use your mouse wheel to rotate. Using %1 mouse wheel will scale the mayor axis, while utilize %2 mouse wheel will scale the minor one.")
						.arg(QKeySequence(Qt::SHIFT).toString(QKeySequence::NativeText),
							 QKeySequence(Qt::CTRL).toString(QKeySequence::NativeText)));

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(annotation_widget_);
  this->setLayout(layout);
}

void AnnotationPage::initializePage() {
  QWizardPage::initializePage();

  // Use original id only if nothing different is given.
  if (next_id_ == std::numeric_limits<int>::min()) {
	next_id_ = QWizardPage::nextId();
  }
}

int AnnotationPage::nextId() const {
  return next_id_;
}

void AnnotationPage::setNextId(int id) {
  next_id_ = id;
  this->setFinalPage(next_id_ == -1);
}

const model::Sample &AnnotationPage::sample() const {
  return qobject_cast<AnnotationWidget *>(annotation_widget_->child())->sample();
}

}