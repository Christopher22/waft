//
// Created by Christopher Gundler on 24.02.2020.
//

#include "AnnotationWidget.h"

#include <QMouseEvent>
#include <QGuiApplication>
#include <QDebug>

#include <utility>

namespace waft::view {

AnnotationWidget::AnnotationWidget(model::Sample sample, QWidget *parent) : QLabel(parent),
																			sample_(std::move(sample)),
																			ellipse_pen_(QColor(255, 59, 48)),
																			major_pen_(QColor(255, 59, 48)),
																			minor_pen_(QColor(255, 59, 48)) {

  this->setScaledContents(true);
  this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  this->setMinimumSize(sample.frame().size());
  this->setPixmap(sample.frame());

  minor_pen_.setStyle(Qt::DashLine);
}

void AnnotationWidget::paintEvent(QPaintEvent *event) {
  QLabel::paintEvent(event);
  sample_.ellipse().draw(this, ellipse_pen_, major_pen_, minor_pen_);
}

void AnnotationWidget::mousePressEvent(QMouseEvent *ev) {
  this->_handleMouse(ev);
}

void AnnotationWidget::mouseMoveEvent(QMouseEvent *ev) {
  if (ev->buttons().testFlag(Qt::LeftButton)) {
	this->_handleMouse(ev);
  }
}

void AnnotationWidget::_handleMouse(QMouseEvent *event) {
  const QPointF local_pos = event->localPos();
  sample_.ellipse().setPosition(float(local_pos.x()) / float(this->width()),
								float(local_pos.y()) / float(this->height()));
  this->update();
}

void AnnotationWidget::wheelEvent(QWheelEvent *event) {
  const QPoint num_pixels = event->pixelDelta();
  const int change = !num_pixels.isNull() ? num_pixels.y() : (event->angleDelta() / 120).y();
  const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();

  if (modifiers.testFlag(Qt::ShiftModifier) || modifiers.testFlag(Qt::ControlModifier)) {
	QPointF axes = sample_.ellipse().axes();
	const QSize size = this->pixmap()->size();
	const float reference = std::max(size.width(), size.height());

	// Handle the mayor axis
	if (modifiers.testFlag(Qt::ShiftModifier)) {
	  double new_x = axes.x() + (float(change) / reference);
	  axes.setX(std::max(new_x, 0.001));
	}

	// Handle the minor axis
	if (modifiers.testFlag(Qt::ControlModifier)) {
	  double new_y = axes.y() + (float(change) / reference);
	  axes.setY(std::max(new_y, 0.001));
	}

	sample_.ellipse().setAxes(axes);
  } else {
	int new_value = int(sample_.ellipse().rotation()) + change;
	if (new_value < 0) {
	  new_value += 360;
	}
	sample_.ellipse().setRotation(float(new_value % 360));
  }

  this->update();
  event->accept();
}

}