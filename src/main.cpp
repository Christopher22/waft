#include "view/Wizard.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  QApplication::setApplicationName("waft");
  QApplication::setApplicationVersion("0.1.0.0");
  QApplication::setOrganizationName("mindQ");

  auto *wizard = new waft::view::Wizard();
  QObject::connect(wizard, &waft::view::Wizard::finished, wizard, [wizard](int) {
	wizard->deleteLater();
  });
  wizard->show();

  return QApplication::exec();
}
