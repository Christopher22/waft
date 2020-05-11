/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Tsv.h"
#include "../../model/Samples.h"
#include "../../model/samples/SavedAnnotations.h"
#include "../util/FileSelector.h"

#include <QVBoxLayout>

namespace waft::view::inputs {

Tsv::Tsv(QWidget *parent)
	: Input(parent), selector_(new util::FileSelector(tr("Please select the existing annotations"),
													  tr("Annotations (*.tsv)"),
													  false,
													  QString(),
													  this)) {

  QObject::connect(selector_, &util::FileSelector::pathSelected, this, [this](const QString &) {
	emit this->imagesChanged();
	emit this->imageAvailabilityChanged();
  });

  auto *layout = new QVBoxLayout();
  layout->addWidget(selector_);
  this->setLayout(layout);
}

model::Samples *Tsv::samples() {
  QString path = selector_->path();
  if (path.isEmpty()) {
	return nullptr;
  }
  return new model::samples::SavedAnnotations(path, nullptr);
}

bool Tsv::isReady() const {
  return static_cast<bool>(*selector_);
}

QString Tsv::inputName() const {
  return tr("Existing annotations: ");
}
}