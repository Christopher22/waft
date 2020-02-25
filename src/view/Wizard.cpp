//
// Created by christopher on 25.02.2020.
//

#include "Wizard.h"
#include "InputPage.h"
#include "OutputPage.h"

waft::view::Wizard::Wizard(QWidget *parent) : QWizard(parent) {
  this->setWindowTitle("waft");
  this->setOption(QWizard::HaveHelpButton, false);
  this->setOption(QWizard::HaveCustomButton1, true);

  this->addPage(new InputPage(this));
  this->addPage(new OutputPage(this));
}
