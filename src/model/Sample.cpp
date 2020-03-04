//
// Created by christopher on 24.02.2020.
//

#include "Sample.h"
#include <QDebug>

namespace waft::model {

Sample::Sample() : path_(), image_(), ellipse_() {

}

Sample::Sample(const QString &path) : path_(path), image_(path), ellipse_() {

}

Sample Sample::parse(const QString &input_line, const QDir &relative_path) {
  QStringList line = input_line.split(Sample::SEPARATOR, Qt::SkipEmptyParts);
  if (line.size() != Sample::HEADERS.size()) {
	return Sample();
  }

  QFileInfo file(line[0]);
  QString file_name = line[0];
  if (file.isRelative()) {
	file_name = relative_path.filePath(file_name);
  } else if (file.isAbsolute() && !file.exists()) {
	// Try to handle invalid absolute file paths in a naive way
	qWarning() << "Absolute path" << file_name << "does not exist. Trying relative file name";
	file_name = relative_path.filePath(file.fileName());
  }

  QVector<float> ellipse_data(Sample::HEADERS.size() - 1);
  bool is_ok = true;
  for (int i = 0; i < ellipse_data.size() && is_ok; ++i) {
	ellipse_data[i] = line[i + 1].toFloat(&is_ok);
  }

  if (is_ok) {
	Sample sample(file_name);
	sample.ellipse_.setPosition(ellipse_data[0], ellipse_data[1]);
	sample.ellipse_.setAxes(ellipse_data[2], ellipse_data[3]);
	sample.ellipse_.setRotation(ellipse_data[4]);
	return sample;
  } else {
	return Sample();
  }
}

Sample::operator bool() const {
  return !image_.isNull();
}

QTextStream &operator<<(QTextStream &stream, const Sample &sample) {
  sample.write(stream, sample.file().dir());
  return stream;
}

void Sample::write(QTextStream &stream, const QDir &parent) const {
  const QString relative_file = parent.relativeFilePath(this->path_.absoluteFilePath());
  const QPointF axes = this->ellipse_.axes(), position = this->ellipse_.position();
  stream << relative_file << '\t' << position.x() << '\t' << position.y() << '\t' << axes.x() << '\t'
		 << axes.y() << "\t" << this->ellipse_.rotation() << '\n';
}

void Sample::writeHeader(QTextStream &stream) {
  for (auto header: Sample::HEADERS) {
	stream << header << Sample::SEPARATOR;
  }
}

}