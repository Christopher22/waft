/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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

