/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
