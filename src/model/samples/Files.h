/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_MODEL_SAMPLES_FILES_H_
#define WAFT_SRC_MODEL_SAMPLES_FILES_H_

#include "../Samples.h"
#include <QStringList>

namespace waft::model::samples {
class Files : public Samples, public QStringList {
 public:
  explicit Files(QObject *parent = nullptr);
  bool load() override;
};
}

#endif //WAFT_SRC_MODEL_SAMPLES_FILES_H_
