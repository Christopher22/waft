//
// Created by christopher on 24.02.2020.
//

#ifndef WAFT_SRC_MODEL_SAMPLE_H_
#define WAFT_SRC_MODEL_SAMPLE_H_

#include "Ellipse.h"

#include <QFileInfo>
#include <QPixmap>
#include <QTextStream>
#include <QDir>

#include <array>

namespace waft::model {
class Sample {
 public:
  static constexpr QChar SEPARATOR = '\t';
  static constexpr std::array<QStringView, 6> HEADERS = {u"file", u"x", u"y", u"major", u"minor", u"rotation"};

  explicit Sample(const QString &path);
  static Sample parse(const QString &input_line, const QDir &relative_path = QDir());

  explicit operator bool() const;
  void write(QTextStream &stream, const QDir &relative_path) const;
  static void writeHeader(QTextStream &stream);

  friend QTextStream &operator<<(QTextStream &stream, const Sample &sample);

  [[nodiscard]] inline const QFileInfo &file() const noexcept {
	return path_;
  }

  [[nodiscard]] inline const QPixmap &frame() const noexcept {
	return image_;
  }

  [[nodiscard]] inline const Ellipse &ellipse() const noexcept {
	return ellipse_;
  }

  [[nodiscard]] inline Ellipse &ellipse() noexcept {
	return ellipse_;
  }

 private:
  Sample();

  QFileInfo path_;
  QPixmap image_;
  Ellipse ellipse_;
};
}

#endif //WAFT_SRC_MODEL_SAMPLE_H_
