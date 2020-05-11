/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_INPUTS_IMAGES_H_
#define WAFT_SRC_VIEW_INPUTS_IMAGES_H_

#include "Input.h"

namespace waft::view {
namespace util {
class FileList;
}

namespace inputs {
class Images : public Input {
 public:
  explicit Images(QWidget *widget = nullptr);
  [[nodiscard]] QString inputName() const override;
  [[nodiscard]] bool isReady() const override;
  model::Samples *samples() override;

 private:
  util::FileList *images_;
};
}
}

#endif //WAFT_SRC_VIEW_INPUTS_IMAGES_H_
