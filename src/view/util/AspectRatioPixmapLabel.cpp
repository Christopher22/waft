//
// Created by Christopher Gundler on 24.02.2020.
//

#include "AspectRatioPixmapLabel.h"

namespace waft::view::util {
AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget *parent) :
    QLabel(parent) {
  this->setMinimumSize(1, 1);
  this->setScaledContents(false);
}

AspectRatioPixmapLabel::AspectRatioPixmapLabel(const QPixmap &pixmap, QWidget *parent)
    : AspectRatioPixmapLabel(parent) {
  AspectRatioPixmapLabel::setPixmap(pixmap);
}

void AspectRatioPixmapLabel::setPixmap(const QPixmap &p) {
  pixmap_ = p;
  QLabel::setPixmap(this->scaledPixmap());
}

int AspectRatioPixmapLabel::heightForWidth(int width) const {
  return pixmap_.isNull() ? this->height() : int(((qreal) pixmap_.height() * width) / pixmap_.width());
}

QSize AspectRatioPixmapLabel::sizeHint() const {
  const int w = this->width();
  return QSize(w, heightForWidth(w));
}

QPixmap AspectRatioPixmapLabel::scaledPixmap() const {
  auto scaled = pixmap_.scaled(this->size() * devicePixelRatioF(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
  scaled.setDevicePixelRatio(devicePixelRatioF());
  return scaled;
}

void AspectRatioPixmapLabel::resizeEvent(QResizeEvent *e) {
  if (!pixmap_.isNull()) {
    QLabel::setPixmap(this->scaledPixmap());
  }
}

}