//
// Created by christopher on 25.02.2020.
//

#include "AnnotationPage.h"
#include "AnnotationWidget.h"

#include <QVBoxLayout>

#include <limits>

namespace waft::view {

AnnotationPage::AnnotationPage(const model::Sample &sample, QWidget *parent)
	: QWizardPage(parent),
	  sample_(sample),
	  annotation_widget_(new AnnotationWidget(sample, this)),
	  next_id_(std::numeric_limits<int>::min()) {
  this->setTitle(QString("Please annotate '%1': ").arg(sample.file().fileName()));

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
  return annotation_widget_->sample();
}

}