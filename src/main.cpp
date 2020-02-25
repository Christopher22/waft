#include "view/Wizard.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication application(argc, argv);

  auto *wizard = new waft::view::Wizard();
  wizard->show();

  return QApplication::exec();
}
