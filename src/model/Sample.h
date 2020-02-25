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

namespace waft::model {
class Sample {
 public:
  explicit Sample(const QString &path);
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
  QFileInfo path_;
  QPixmap image_;
  Ellipse ellipse_;
};
}

#endif //WAFT_SRC_MODEL_SAMPLE_H_
