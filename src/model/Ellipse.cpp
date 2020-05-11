/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Ellipse.h"

#include <QPaintDevice>
#include <QPainter>

#include <algorithm>

namespace waft::model {

Ellipse::Ellipse(float x, float y, float mayor_axis, float minor_axis, float rotation) noexcept: Ellipse() {
  this->setAxes(mayor_axis, minor_axis);
  const bool result = this->setPosition(x, y) && this->setRotation(rotation);
  Q_ASSERT(result);
}

void Ellipse::setAxes(float mayor, float minor) noexcept {
  mayor_ = mayor;
  minor_ = minor;
  if (minor_ > mayor_) {
    std::swap(minor_, mayor_);
  }
}

bool Ellipse::setPosition(float x, float y) noexcept {
  if (x < 0 || x > 1 || y < 0 || y > 1) {
    return false;
  }
  x_ = x;
  y_ = y;
  return true;
}

bool Ellipse::setRotation(float rotation) noexcept {
  rotation_ = fmod(rotation, 360);
  if (rotation_ < 0)
    rotation_ += 360;
  return true;
}

void Ellipse::draw(QPaintDevice *painting_area,
                   const QPen &pen,
                   const QPen &major_pen,
                   const QPen &minor_pen) const {
  QPainter painter(painting_area);
  painter.setPen(pen);
  painter.setRenderHint(QPainter::Antialiasing);

  const QSize size = QSize(painting_area->width(), painting_area->height());
  const float reference_size = std::max(size.width(), size.height());
  const int x = int(x_ * float(size.width()));
  const int y = int(y_ * float(size.height()));
  const int mayor_size = int(mayor_ * reference_size);
  const int minor_size = int(minor_ * reference_size);

  painter.translate(x, y);
  painter.rotate(rotation_);
  painter.translate(-x, -y);

  painter.drawEllipse(x - mayor_size,
                      y - minor_size,
                      mayor_size * 2,
                      minor_size * 2);

  painter.setPen(major_pen);
  painter.drawLine(x, y, x + mayor_size, y);

  painter.setPen(minor_pen);
  painter.drawLine(x, y, x, y + minor_size);
}

}