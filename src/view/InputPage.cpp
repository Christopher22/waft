/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "InputPage.h"
#include "../model/Samples.h"
#include "util/FileList.h"
#include "inputs/Input.h"
#include "inputs/MultiInput.h"
#include "inputs/Images.h"
#include "inputs/Tsv.h"
#include "AnnotationPage.h"
#include "OutputPage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QThread>

namespace waft::view {

InputPage::InputPage(QWidget *parent)
	: QWizardPage(parent),
	  main_widget_(new inputs::MultiInput({new inputs::Images(), new inputs::Tsv()}, this)),
	  worker_(nullptr) {
  this->setTitle(tr("Define input"));
  this->setSubTitle(
	  tr("Please specify if you rather want to annotate new frames or open existing annotations. Afterward, click 'Load samples' and 'Commit' to proceed."));
  this->setCommitPage(true);

  // Redirect the signal
  QObject::connect(main_widget_,
				   &inputs::Input::imageAvailabilityChanged,
				   this,
				   &InputPage::_onDataAvailabilityChanged);
  QObject::connect(main_widget_, &inputs::Input::imagesChanged, this, &InputPage::_onSamplesChanged);

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
  this->setButtonText(QWizard::CustomButton1, tr("Load samples"));
  QObject::connect(button, &QAbstractButton::clicked, this, &InputPage::_loadData);

  // Hide the checkbox and enable cancel
  this->wizard()->button(QWizard::CustomButton2)->setVisible(false);
  auto *cancel = this->wizard()->button(QWizard::CancelButton);
  if (cancel != nullptr) {
	cancel->setEnabled(true);
	cancel->setVisible(true);
  }
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
  Q_ASSERT(main_widget_->isReady());
  Q_ASSERT(worker_ == nullptr);

  QAbstractButton *button = this->wizard()->button(QWizard::CustomButton1);
  button->setEnabled(false);
  button->setText(tr("Loading samples..."));
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
  this->wizard()->button(QWizard::CustomButton1)->setEnabled(main_widget_->isReady());
}

void InputPage::_onLoadedSample(const model::Sample &sample) {
  const auto index = annotation_page_indices_.size();
  annotation_page_indices_
	  .append(this->wizard()->addPage(new AnnotationPage(sample, index, this)));
}

void InputPage::_onFailedSample(const model::Sample &sample) {
  QMessageBox::warning(this,
					   tr("Unable to load sample"),
					   tr("An error occurred while trying to load '%1'.").arg(sample.file().absoluteFilePath()));
}

void InputPage::_onDone() {
  this->_cleanWorker();
  this->setButtonText(QWizard::CustomButton1, tr("Samples loaded"));
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
  button->setEnabled(main_widget_->isReady());
  button->setText(tr("Load samples"));

  emit this->completeChanged();
}

}