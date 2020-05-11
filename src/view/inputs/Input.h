/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
