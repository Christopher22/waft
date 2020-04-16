//
// Created by christopher on 25.02.2020.
//

#include "Wizard.h"
#include "InputPage.h"
#include "OutputPage.h"

#include <QCheckBox>

waft::view::Wizard::Wizard(QWidget *parent) : QWizard(parent, Wizard::flags()) {
  // Create the checkbox for excluding frames
  auto *include_frame = new QCheckBox("Include frame", this);
  include_frame->setChecked(true);

  this->setWindowTitle(tr("waft: Annotating pupils with ease"));
  this->setButton(QWizard::CustomButton2, include_frame);
  this->setOption(QWizard::HaveHelpButton, false);
  this->setOption(QWizard::HaveCustomButton1, true);
  this->setOption(QWizard::HaveCustomButton2, true);
  this->setOption(QWizard::IndependentPages, false);
  this->addPage(new InputPage(this));
  this->addPage(new OutputPage(this));
}

Qt::WindowFlags waft::view::Wizard::flags() {
  return Qt::WindowFlags(
	  Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
}
