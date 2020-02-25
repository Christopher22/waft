//
// Created by christopher on 25.02.2020.
//

#include "OutputPage.h"
#include "util/FileSelector.h"
#include <QVBoxLayout>

namespace waft::view {

OutputPage::OutputPage(QWidget *parent) : QWizardPage(parent), QVector<AnnotationPage *>() {
  this->setTitle("Please specify the output file");
  this->setFinalPage(true);

  auto *file = new util::FileSelector("Please select the output file", "Tab-separated values (*.tsv)", true, this);
  this->registerField("output_file*", file, "path", SIGNAL(pathSelected(QString)));

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(file);
  this->setLayout(layout);
}

int OutputPage::nextId() const {
  return -1;
}

}