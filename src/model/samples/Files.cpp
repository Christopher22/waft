/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Files.h"

#include "../Samples.h"

namespace waft::model::samples {

Files::Files(QObject *parent) : Samples(parent), QStringList() {

}

bool Files::load() {
  for (auto &image_path: *this) {
	Sample sample(image_path);
	if (sample) {
	  sample.setMeaningful(true);
	  emit this->loaded(sample);
	} else {
	  emit this->failure(sample);
	}
  }
  emit this->done();
  return true;
}

}