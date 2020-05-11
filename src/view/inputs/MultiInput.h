/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
