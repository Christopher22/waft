#ifndef BUILD_TESTING
#include "view/Wizard.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  QApplication::setApplicationName("waft");
  QApplication::setApplicationVersion("0.1.2.1");
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