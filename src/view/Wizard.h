//
// Created by christopher on 25.02.2020.
//

#ifndef WAFT_SRC_VIEW_WIZARD_H_
#define WAFT_SRC_VIEW_WIZARD_H_

#include <QWizard>

namespace waft::view {
class Wizard : public QWizard {
 public:
  explicit Wizard(QWidget *parent = nullptr);
};
}

#endif //WAFT_SRC_VIEW_WIZARD_H_
