//
// Created by Christopher Gundler on 24.02.2020.
//

#ifndef WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_
#define WAFT_SRC_VIEW_ANNOTATIONWIDGET_H_

#include "../model/Sample.h"
#include <QLabel>

namespace waft::view {
class AnnotationWidget : public QLabel {
 Q_OBJECT

 public:
  explicit AnnotationWidget(model::Sample sample, QWidget *parent = nullptr);
  [[nodiscard]] const model::Sample &sample() const {
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
