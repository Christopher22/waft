//
// Created by christopher on 24.02.2020.
//

#ifndef WAFT_SRC_MODEL_SAMPLE_H_
#define WAFT_SRC_MODEL_SAMPLE_H_

#include "Ellipse.h"

#include <QFileInfo>
#include <QPixmap>

namespace waft::model {
class Sample {
 public:
  explicit Sample(const QString &path);
  explicit operator bool() const;

  [[nodiscard]] inline const QFileInfo &file() const noexcept {
	return path_;
  }

  [[nodiscard]] inline const QPixmap &frame() const noexcept {
	return image_;
  }

  [[nodiscard]] inline const Ellipse &ellipse() const noexcept {
	return ellipse_;
  }

 private:
  QFileInfo path_;
  QPixmap image_;
  Ellipse ellipse_;
};
}

#endif //WAFT_SRC_MODEL_SAMPLE_H_
