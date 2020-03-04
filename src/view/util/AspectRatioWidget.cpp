//
// Created by christopher on 04.03.2020.
//

#include "AspectRatioWidget.h"
#include <QBoxLayout>
#include <QResizeEvent>

#include <cmath>

namespace waft::view::util {

AspectRatioWidget::AspectRatioWidget(QWidget *widget, QWidget *parent) :
	QWidget(parent), child_(widget), aspect_ratio_(float(widget->size().width()) / float(widget->size().height())) {
  child_->setParent(this);

  layout = new QBoxLayout(QBoxLayout::LeftToRight, this);

  // add spacer, then your widget, then spacer
  layout->addItem(new QSpacerItem(0, 0));
  layout->addWidget(widget);
  layout->addItem(new QSpacerItem(0, 0));
}

void AspectRatioWidget::resizeEvent(QResizeEvent *event) {
  float thisAspectRatio = float(event->size().width()) / float(event->size().height());
  int widgetStretch, outerStretch;

  if (thisAspectRatio > aspect_ratio_) {
	layout->setDirection(QBoxLayout::LeftToRight);
	widgetStretch = int(float(this->height()) * aspect_ratio_);
	outerStretch = std::lround(float(this->width() - widgetStretch) / 2.0f);
  } else {
	layout->setDirection(QBoxLayout::TopToBottom);
	widgetStretch = int(float(this->width()) * aspect_ratio_); // i.e., my height
	outerStretch = std::lround(float(this->height() - widgetStretch) / 2.0f);
  }

  layout->setStretch(0, outerStretch);
  layout->setStretch(1, widgetStretch);
  layout->setStretch(2, outerStretch);
}
}