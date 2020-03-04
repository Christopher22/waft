//
// Created by christopher on 24.02.2020.
//

#include "Files.h"

#include "../Samples.h"

namespace waft::model::samples {

Files::Files(QObject *parent) : Samples(parent), QStringList() {

}

bool Files::load() {
  for (auto &image_path: *this) {
	Sample sample(image_path);
	if (sample) {
	  emit this->loaded(sample);
	} else {
	  emit this->failure(sample);
	}
  }
  emit this->done();
  return true;
}

}