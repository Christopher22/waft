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
  ellipse_.draw(this, ellipse_pen_, this->getImageRect());
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
  const QRect image_size = this->getImageRect();
  const QPointF local_pos = event->localPos() - image_size.topLeft();
  if (local_pos.x() <= image_size.width() && local_pos.y() <= image_size.height()) {
	ellipse_.setPosition(float(local_pos.x()) / float(image_size.width()),
						 float(local_pos.y()) / float(image_size.height()));
	this->update();
  }
}

void AnnotationWidget::wheelEvent(QWheelEvent *event) {
  const QPoint num_pixels = event->pixelDelta();
  const int change = !num_pixels.isNull() ? num_pixels.y() : (event->angleDelta() / 120).y();
  const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();

  if (modifiers.testFlag(Qt::ShiftModifier) || modifiers.testFlag(Qt::ControlModifier)) {
	QPointF axes = ellipse_.axes();
	const QSize size = this->pixmap()->size();
	const float reference = std::max(size.width(), size.height());

	// Handle the mayor axis
	if (modifiers.testFlag(Qt::ShiftModifier)) {
	  axes.setX(axes.x() + (float(change) / reference));
	}

	// Handle the minor axis
	if (modifiers.testFlag(Qt::ControlModifier)) {
	  axes.setY(axes.y() + (float(change) / reference));
	}

	ellipse_.setAxes(axes);
  } else {
	int new_value = int(ellipse_.rotation()) + change;
	if (new_value < 0) {
	  new_value += 360;
	}
	ellipse_.setRotation(float(new_value % 360));
  }

  this->update();
  event->accept();
}

QRect AnnotationWidget::getImageRect() const {
  const QSize image_size = this->pixmap()->size(), widget_size = this->size();
  return image_size != widget_size ?
		 QRect(0, (widget_size.height() - image_size.height()) / 2, image_size.width(), image_size.height()) :
		 QRect(0, 0, widget_size.width(), widget_size.height());
}

}