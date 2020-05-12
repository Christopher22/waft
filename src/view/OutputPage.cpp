/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "OutputPage.h"
#include "AnnotationPage.h"
#include "util/FileSelector.h"
#include "../model/Samples.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QCheckBox>

namespace waft::view {

OutputPage::OutputPage(QWidget *parent)
	: QWizardPage(parent),
	  QVector<AnnotationPage *>(),
	  file_(new util::FileSelector(tr("Please select the output file"),
								   tr("Annotation (*.tsv)"),
								   true,
								   QString(),
								   this)),
	  include_excluded_(new QCheckBox(tr("Include unannotated samples"), this)) {
  this->setTitle(tr("Define output"));
  this->setSubTitle(tr(
	  "Please specify the file the annotated pupils are saved in. If choosing an existing file, you may overwrite it or append the new annotations."));
  this->setFinalPage(true);
  this->registerField("output_file*", file_, "path", SIGNAL(pathSelected(QString)));

  (*file_)->setFlag(QFileDialog::DontConfirmOverwrite, true);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(file_);
  layout->addWidget(include_excluded_);
  this->setLayout(layout);
}

int OutputPage::nextId() const {
  return -1;
}

bool OutputPage::validatePage() {
  QFile data(file_->path());
  const bool should_append = data.exists() && QMessageBox::question(this,
																	tr("File already exists"),
																	tr("The selected file does already exist. Do you want to append the data? Otherwise, it is overwritten!"),
																	QMessageBox::StandardButtons(
																		QMessageBox::Yes | QMessageBox::No),
																	QMessageBox::Yes) == QMessageBox::Yes;

  // Define if existing file should be overwritten
  if (!data.open(QFile::WriteOnly | (should_append ? QFile::Append : QFile::Truncate))) {
	QMessageBox::warning(this,
						 tr("Opening file failed"),
						 tr("Opening the selected file failed. Do you have the required rights?"));
	return false;
  }

  // Open the stream and write the header
  QTextStream stream(&data);
  if (!should_append) {
	model::Sample::writeHeader(stream);
  }

  // Write the ellipses
  const QDir directory = QFileInfo(file_->path()).dir();
  for (auto page: *this) {
	if (!page->sample().isMeaningful() && !include_excluded_->isChecked()) {
	  continue;
	}
	page->sample().write(stream, directory);
  }

  return true;
}

void OutputPage::initializePage() {
  QWizardPage::initializePage();

  // Set a useful default for the file selection
  if (!this->empty()) {
	file_->setRoot((*this)[0]->sample().file().dir().absolutePath());
  }

  // Enable cancel button
  auto *cancel = this->wizard()->button(QWizard::CancelButton);
  if (cancel != nullptr) {
	cancel->setEnabled(true);
	cancel->setVisible(true);
  }
}

}