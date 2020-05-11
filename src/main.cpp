/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef BUILD_TESTING
#include "view/Wizard.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  QApplication::setApplicationName("waft");
  QApplication::setApplicationVersion("0.2.2.0");
  QApplication::setOrganizationName("mindQ");

  auto *wizard = new waft::view::Wizard();
  QObject::connect(wizard, &waft::view::Wizard::finished, wizard, [wizard](int) {
	wizard->deleteLater();
  });
  wizard->show();

  return QApplication::exec();
}
#else
#include "Tests.h"
QTEST_MAIN(Tests)
#endif