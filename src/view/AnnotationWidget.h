//
// Created by Christopher Gundler on 24.02.2020.
//

#ifndef WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_
#define WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_

#include "util/AspectRatioPixmapLabel.h"
#include "../model/Ellipse.h"

namespace waft::view {
class AnnotationWidget : public util::AspectRatioPixmapLabel {
 public:
  explicit AnnotationWidget(const QPixmap &pixmap, QWidget *parent = nullptr);
  [[nodiscard]] inline model::Ellipse ellipse() const {
	return ellipse_;
  }

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *ev) override;
  void mouseMoveEvent(QMouseEvent *ev) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  [[nodiscard]] QRect getImageRect() const;
  void _handleMouse(QMouseEvent *event);

  model::Ellipse ellipse_;
  QPen ellipse_pen_;
};
}

#endif //WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_
