//
// Created by christopher on 25.02.2020.
//

#include "Samples.h"

#include <QImageReader>

namespace waft::model {

QStringList Samples::supportedFormats() {
  QList<QByteArray> formats_raw = QImageReader::supportedImageFormats();
  QStringList result;
  result.reserve(formats_raw.size());
  for (auto &format_raw: formats_raw) {
	result.push_back(format_raw);
  }
  return result;
}

}