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
  stream << "file\tx\ty\tmajor\tminor\trotation\n";
}

}