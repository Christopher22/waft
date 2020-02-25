//
// Created by christopher on 25.02.2020.
//

#include "OutputPage.h"
#include "AnnotationPage.h"
#include "util/FileSelector.h"
#include "../model/Samples.h"

#include <QVBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

namespace waft::view {

OutputPage::OutputPage(QWidget *parent)
	: QWizardPage(parent),
	  QVector<AnnotationPage *>(),
	  file_(new util::FileSelector("Please select the output file",
								   "Tab-separated values (*.tsv)",
								   true,
								   QString(),
								   this)) {
  this->setTitle("Please specify the output file");
  this->setFinalPage(true);
  this->registerField("output_file*", file_, "path", SIGNAL(pathSelected(QString)));

  (*file_)->setFlag(QFileDialog::DontConfirmOverwrite, true);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(file_);
  this->setLayout(layout);
}

int OutputPage::nextId() const {
  return -1;
}

bool OutputPage::validatePage() {
  QFile data(file_->path());
  const bool should_append = data.exists() && QMessageBox::question(this,
																	"File already exists",
																	"The selected file does already exist. Do you want to append the data? Otherwise, it is overwritten!",
																	QMessageBox::StandardButtons(
																		QMessageBox::Yes | QMessageBox::No),
																	QMessageBox::Yes) == QMessageBox::Yes;

  // Define if existing file should be overwritten
  if (!data.open(QFile::WriteOnly | (should_append ? QFile::Append : QFile::Truncate))) {
	QMessageBox::warning(this,
						 "Opening file failed",
						 "Opening the selected file failed. Do you have the required rights?");
	return false;
  }

  // Open the stream and write the header
  QTextStream stream(&data);
  if (!should_append) {
	model::Sample::writeHeader(stream);
  }

  // Write the ellipses
  for (auto page: *this) {
	const QDir directory = QFileInfo(file_->path()).dir();
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