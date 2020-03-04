//
// Created by christopher on 04.03.2020.
//

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