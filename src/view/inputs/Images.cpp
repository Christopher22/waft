/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Images.h"
#include "../util/FileList.h"
#include "../../model/samples/Files.h"

#include <QVBoxLayout>

namespace waft::view::inputs {

Images::Images(QWidget *widget)
	: Input(widget), images_(new util::FileList(model::samples::Files::supportedFormats(), this)) {
  QObject::connect(images_, &util::FileList::fileAvailabilityChanged, this, [this] {
	emit this->imageAvailabilityChanged();
  });
  QObject::connect(images_, &util::FileList::filesChanged, this, [this] {
	emit this->imagesChanged();
  });

  auto *layout = new QVBoxLayout();
  layout->addWidget(images_);
  this->setLayout(layout);
}

QString Images::inputName() const {
  return tr("Frames: ");
}

bool Images::isReady() const {
  return images_->filesAvailable();
}

model::Samples *Images::samples() {
  if (!this->isReady()) {
	return nullptr;
  }

  auto *samples = new model::samples::Files(nullptr);
  samples->reserve(images_->count());
  for (int row = 0, size = images_->count(); row < size; ++row) {
	samples->append(images_->item(row)->data(Qt::UserRole).toString());
  }
  return samples;
}

}