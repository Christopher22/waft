//
// Created by christopher on 25.02.2020.
//

#include "InputPage.h"
#include "InputWidget.h"
#include "AnnotationPage.h"
#include "OutputPage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QThread>

namespace waft::view {

InputPage::InputPage(QWidget *parent) : QWizardPage(parent), main_widget_(new InputWidget(this)), worker_(nullptr) {
  this->setTitle("Please specify the input data");
  this->setCommitPage(true);

  // Redirect the signal
  QObject::connect(main_widget_, &InputWidget::completeChanged, this, &InputPage::_onDataAvailabilityChanged);
  QObject::connect(main_widget_, &InputWidget::samplesChanged, this, &InputPage::_onSamplesChanged);

  auto *layout = new QVBoxLayout();
  layout->addWidget(main_widget_);
  this->setLayout(layout);
}

InputPage::~InputPage() {
  this->_cleanWorker();
}

void InputPage::initializePage() {
  QWizardPage::initializePage();

  QAbstractButton *button = this->wizard()->button(QWizard::CustomButton1);
  button->setVisible(true);
  button->setEnabled(false);
  this->setButtonText(QWizard::CustomButton1, "Load samples");
  QObject::connect(button, &QAbstractButton::clicked, this, &InputPage::_loadData);
}

bool InputPage::validatePage() {
  if (!QWizardPage::validatePage()) {
	return false;
  }

  QAbstractButton *button = this->wizard()->button(QWizard::CustomButton1);
  button->setVisible(false);
  QObject::disconnect(button, &QAbstractButton::clicked, this, &InputPage::_loadData);
  return true;
}

bool InputPage::isComplete() const {
  return QWizardPage::isComplete() && !annotation_page_indices_.empty();
}

int InputPage::nextId() const {
  return annotation_page_indices_.empty() ? QWizardPage::nextId() : annotation_page_indices_[0];
}

void InputPage::_loadData() {
  Q_ASSERT(main_widget_->isComplete());
  Q_ASSERT(worker_ == nullptr);

  QAbstractButton *button = this->wizard()->button(QWizard::CustomButton1);
  button->setEnabled(false);
  button->setText("Loading samples...");
  main_widget_->setEnabled(false);

  // Create the sample loader
  model::Samples *samples = main_widget_->samples();

  worker_ = new QThread(nullptr);
  QObject::connect(worker_, &QThread::finished, samples, &QObject::deleteLater);
  QObject::connect(this, &InputPage::_startBackgroundJob, samples, &model::Samples::load);
  QObject::connect(samples, &model::Samples::loaded, this, &InputPage::_onLoadedSample);
  QObject::connect(samples, &model::Samples::failure, this, &InputPage::_onFailedSample);
  QObject::connect(samples, &model::Samples::done, this, &InputPage::_onDone);
  worker_->start();
  emit this->_startBackgroundJob();
}

void InputPage::_onDataAvailabilityChanged() {
  this->wizard()->button(QWizard::CustomButton1)->setEnabled(main_widget_->isComplete());
}

void InputPage::_onLoadedSample(const model::Sample &sample) {
  annotation_page_indices_.append(this->wizard()->addPage(new AnnotationPage(sample, this)));
}

void InputPage::_onFailedSample(const model::Sample &sample) {
  QMessageBox::warning(this,
					   "Unable to load sample",
					   QString("An error occurred while trying to load '%1'.").arg(sample.file().absolutePath()));
}

void InputPage::_onDone() {
  this->_cleanWorker();
  this->setButtonText(QWizard::CustomButton1, "Samples loaded");
  main_widget_->setEnabled(true);
  if (!annotation_page_indices_.empty()) {
	auto *output = qobject_cast<OutputPage *>(this->wizard()->page(QWizardPage::nextId()));
	output->clear();
	output->reserve(annotation_page_indices_.size());
	for (auto id: annotation_page_indices_) {
	  output->push_back(qobject_cast<AnnotationPage *>(this->wizard()->page(id)));
	}

	// Let the last annotation page redirect to the output
	qobject_cast<AnnotationPage *>(this->wizard()->page(annotation_page_indices_.last()))
		->setNextId(QWizardPage::nextId());
	emit this->completeChanged();
  }
}

void InputPage::_cleanWorker() {
  if (worker_ != nullptr) {
	worker_->quit();
	worker_->wait();
	worker_->deleteLater();
	worker_ = nullptr;
  }
}

void InputPage::_onSamplesChanged() {
  // Do nothing, if no samples were loaded.
  if (annotation_page_indices_.empty()) {
	return;
  }

  // Delete all created samples
  for (auto id: annotation_page_indices_) {
	this->wizard()->removePage(id);
  }
  annotation_page_indices_.clear();

  QAbstractButton *button = this->wizard()->button(QWizard::CustomButton1);
  button->setEnabled(main_widget_->isComplete());
  button->setText("Load samples");

  emit this->completeChanged();
}

}