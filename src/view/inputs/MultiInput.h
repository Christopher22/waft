//
// Created by christopher on 04.03.2020.
//

#ifndef WAFT_SRC_VIEW_INPUTS_MULTIINPUT_H_
#define WAFT_SRC_VIEW_INPUTS_MULTIINPUT_H_

#include <QWidget>
#include "Input.h"

#include <initializer_list>

class QButtonGroup;
namespace waft::view::inputs {

class MultiInput : public Input {
 Q_OBJECT

 public:
  MultiInput(std::initializer_list<Input *> inputs, QWidget *parent = nullptr);
  [[nodiscard]] bool isReady() const override;
  [[nodiscard]] QString inputName() const override;
  model::Samples *samples() override;

 private:
  void _setCurrentInput(int next_index);

  QVector<Input *> inputs_;
  QButtonGroup *buttons_;
  int current_id_;
};
}

#endif //WAFT_SRC_VIEW_INPUTS_MULTIINPUT_H_
