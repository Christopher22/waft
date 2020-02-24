//
// Created by Christopher Gundler on 24.02.2020.
//

#include "AnnotationWidget.h"

#include <QMouseEvent>
#include <QGuiApplication>

namespace waft::view {

AnnotationWidget::AnnotationWidget(const QPixmap &pixmap, QWidget *parent) : AspectRatioPixmapLabel(pixmap, parent),
                                                                             ellipse_pen_(QColor(255, 59, 48)) {

}

void AnnotationWidget::paintEvent(QPaintEvent *event) {
  AspectRatioPixmapLabel::paintEvent(event);
  ellipse_.draw(this, ellipse_pen_);
}

void AnnotationWidget::mousePressEvent(QMouseEvent *ev) {
  AspectRatioPixmapLabel::mousePressEvent(ev);
  this->_handleMouse(ev);
}

void AnnotationWidget::mouseMoveEvent(QMouseEvent *ev) {
  AspectRatioPixmapLabel::mouseMoveEvent(ev);
  if (ev->buttons().testFlag(Qt::LeftButton)) {
    this->_handleMouse(ev);
  }
}

void AnnotationWidget::_handleMouse(QMouseEvent *event) {
  QPointF local_pos = event->localPos();
  const QSize size = this->size();
  ellipse_.setPosition(float(local_pos.x()) / float(size.width()), float(local_pos.y()) / float(size.height()));
  this->update();
}

void AnnotationWidget::wheelEvent(QWheelEvent *event) {
  const QPoint num_pixels = event->pixelDelta();
  const int change = !num_pixels.isNull() ? num_pixels.y() : (event->angleDelta() / 120).y();
  const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();

  if (modifiers.testFlag(Qt::ShiftModifier) || modifiers.testFlag(Qt::ControlModifier)) {
    QPointF axes = ellipse_.axes();
    const QSize size = this->pixmap()->size();
    const float reference = std::max(size.width(), size.height());

    if (modifiers.testFlag(Qt::ShiftModifier)) {
      axes.setX(axes.x() + (float(change) / reference));
    }
    if (modifiers.testFlag(Qt::ControlModifier)) {
      axes.setY(axes.y() + (float(change) / reference));
    }

    ellipse_.setAxes(axes);
  } else {
    ellipse_.setRotation(float((int(ellipse_.rotation()) + change) % 360));
  }

  this->update();
  event->accept();
}

}