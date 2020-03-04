//
// Created by christopher on 02.03.2020.
//

#include "SavedAnnotations.h"
#include <QTextStream>
#include <QFileInfo>

namespace waft::model::samples {

SavedAnnotations::SavedAnnotations(const QString &file, QObject *parent) : Samples(parent), file_(file) {

}

bool SavedAnnotations::load() {
  if (!file_.open(QFile::ReadOnly)) {
	return false;
  }

  QTextStream data(&file_);
  QString line;
  for (int line_num = 0; data.readLineInto(&line); ++line_num) {
	// Do not try to parse header
	if (line_num == 0 && line.startsWith(Sample::HEADERS[0])) {
	  continue;
	}

	Sample sample = Sample::parse(line, QFileInfo(file_.fileName()).dir());
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

