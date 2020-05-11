/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_
#define WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_

#include "../model/Sample.h"
#include <QLabel>

namespace waft::view {
class AnnotationWidget : public QLabel {
 Q_OBJECT

 public:
  explicit AnnotationWidget(model::Sample sample, QWidget *parent = nullptr);
  [[nodiscard]] const model::Sample &sample() const noexcept {
	return sample_;
  }
  [[nodiscard]] model::Sample &sample() noexcept {
	return sample_;
  }

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *ev) override;
  void mouseMoveEvent(QMouseEvent *ev) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  void _handleMouse(QMouseEvent *event);

  model::Sample sample_;
  QPen ellipse_pen_, major_pen_, minor_pen_;
};
}

#endif //WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_
