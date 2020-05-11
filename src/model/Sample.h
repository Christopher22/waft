/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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

  void setMeaningful(bool meaningful) noexcept {
	include_ = meaningful;
  }

  [[nodiscard]] inline const QFileInfo &file() const noexcept {
	return path_;
  }

  [[nodiscard]] inline const QPixmap &frame() const noexcept {
	return image_;
  }

  [[nodiscard]] inline bool isMeaningful() const noexcept {
	return include_;
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
  bool include_;
};
}

#endif //WAFT_SRC_MODEL_SAMPLE_H_
