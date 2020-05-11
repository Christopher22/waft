/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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