//
// Created by christopher on 24.02.2020.
//

#include "Sample.h"

namespace waft::model {

Sample::Sample(const QString &path) : path_(path), image_(path), ellipse_() {

}

Sample::operator bool() const {
  return !image_.isNull();
}

}