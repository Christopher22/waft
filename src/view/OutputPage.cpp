//
// Created by christopher on 25.02.2020.
//

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
}

}