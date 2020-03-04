//
// Created by christopher on 25.02.2020.
//

#include "Wizard.h"
#include "InputPage.h"
#include "OutputPage.h"

waft::view::Wizard::Wizard(QWidget *parent) : QWizard(parent, Wizard::flags()) {
  this->setWindowTitle(tr("waft: Annotating pupils with ease"));
  this->setOption(QWizard::HaveHelpButton, false);
  this->setOption(QWizard::HaveCustomButton1, true);

  this->addPage(new InputPage(this));
  this->addPage(new OutputPage(this));
}

Qt::WindowFlags waft::view::Wizard::flags() {
  return Qt::WindowFlags(
	  Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
}
