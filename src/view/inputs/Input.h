//
// Created by christopher on 04.03.2020.
//

#ifndef WAFT_SRC_VIEW_INPUTS_INPUT_H_
#define WAFT_SRC_VIEW_INPUTS_INPUT_H_

#include <QWidget>

namespace waft {
namespace model {
class Samples;
}

namespace view::inputs {
class Input : public QWidget {
 Q_OBJECT

 public:
  explicit Input(QWidget *parent = nullptr) : QWidget(parent) {}
  [[nodiscard]] virtual QString inputName() const = 0;
  [[nodiscard]] virtual bool isReady() const = 0;
  virtual model::Samples *samples() = 0;

 signals:
  void imageAvailabilityChanged();
  void imagesChanged();
};
}
}

#endif //WAFT_SRC_VIEW_INPUTS_INPUT_H_
