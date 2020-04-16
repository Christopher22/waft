//
// Created by christopher on 24.02.2020.
//

#include "Sample.h"
#include <QDebug>

namespace waft::model {

Sample::Sample() : path_(), image_(), ellipse_(), include_(false) {

}

Sample::Sample(const QString &path) : path_(path), image_(path), ellipse_(), include_(false) {
}

Sample Sample::parse(const QString &input_line, const QDir &relative_path) {
  QStringList line = input_line.split(Sample::SEPARATOR, Qt::KeepEmptyParts);
  if (line.empty()) {
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

  // Create a default sample which should not be included by default
  Sample sample(file_name);
  if (line.size() >= Sample::HEADERS.size()) {
	// Parse the floats
	QVector<float> ellipse_data(Sample::HEADERS.size() - 1);
	bool is_ok = true;
	for (int i = 0; i < ellipse_data.size() && is_ok; ++i) {
	  ellipse_data[i] = line[i + 1].toFloat(&is_ok);
	}

	// Fill the ellipse with the actual data
	if (is_ok) {
	  sample.ellipse_.setPosition(ellipse_data[0], ellipse_data[1]);
	  sample.ellipse_.setAxes(ellipse_data[2], ellipse_data[3]);
	  sample.ellipse_.setRotation(ellipse_data[4]);
	  sample.include_ = true;
	}
  }

  return sample;
}

Sample::operator bool() const {
  return !image_.isNull();
}

void Sample::write(QTextStream &stream, const QDir &parent) const {
  stream << parent.relativeFilePath(this->path_.absoluteFilePath());
  if (include_) {
	const QPointF axes = this->ellipse_.axes(), position = this->ellipse_.position();
	stream << '\t' << position.x() << '\t' << position.y() << '\t' << axes.x() << '\t'
		   << axes.y() << "\t" << this->ellipse_.rotation();
  }
  stream << '\n';
}

QTextStream &operator<<(QTextStream &stream, const Sample &sample) {
  sample.write(stream, sample.file().dir());
  return stream;
}

void Sample::writeHeader(QTextStream &stream) {
  for (auto header: Sample::HEADERS) {
	stream << header << Sample::SEPARATOR;
  }
  stream << endl;
}

}