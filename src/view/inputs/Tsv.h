/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_INPUTTSVWIDGET_H_
#define WAFT_SRC_VIEW_INPUTTSVWIDGET_H_

#include "Input.h"

namespace waft {
namespace model {
class Samples;
}

namespace view {
namespace util {
class FileSelector;
}

namespace inputs {
class Tsv : public Input {
 public:
  explicit Tsv(QWidget *parent = nullptr);
  [[nodiscard]] bool isReady() const override;
  [[nodiscard]] QString inputName() const override;
  model::Samples *samples() override;

 private:
  util::FileSelector *selector_;
};
}
}
}

#endif //WAFT_SRC_VIEW_INPUTTSVWIDGET_H_
