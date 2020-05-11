/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_MODEL_ELLIPSE_H_
#define WAFT_SRC_MODEL_ELLIPSE_H_

#include <QPointF>
#include <QPen>

class QPaintDevice;

namespace waft::model {
class Ellipse {
 public:
  constexpr Ellipse() noexcept: x_(0.5), y_(0.5), mayor_(0.1), minor_(0.05), rotation_(0) {}
  Ellipse(float x, float y, float mayor_axis, float minor_axis, float rotation) noexcept;
  void setAxes(float mayor, float minor) noexcept;
  bool setPosition(float x, float y) noexcept;
  bool setRotation(float rotation) noexcept;

  void draw(QPaintDevice *painting_area, const QPen &pen, const QPen &major_pen, const QPen &minor_pen) const;

  inline bool setPosition(const QPointF &point) noexcept {
	return setPosition(point.x(), point.y());
  }

  inline void setAxes(const QPointF &point) noexcept {
	setAxes(point.x(), point.y());
  }

  [[nodiscard]] inline QPointF position() const noexcept {
	return QPointF(x_, y_);
  }

  [[nodiscard]] inline QPointF axes() const noexcept {
	return QPointF(mayor_, minor_);
  }

  [[nodiscard]] inline float rotation() const noexcept {
	return rotation_;
  }
  
 private:
  float x_, y_, mayor_, minor_, rotation_;
};
}

#endif //WAFT_SRC_MODEL_ELLIPSE_H_
