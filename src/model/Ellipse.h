//
// Created by Christopher Gundler on 24.02.2020.
//

#ifndef WAFT_SRC_MODEL_ELLIPSE_H_
#define WAFT_SRC_MODEL_ELLIPSE_H_

#include <QPointF>
#include <QPen>

class QPaintDevice;

namespace waft::model {
class Ellipse {
 public:
  constexpr Ellipse() noexcept: x_(0.5), y_(0.5), mayor_(0.1), minor_(0.05), rotation_(0) {}
  Ellipse(float x, float y, float mayor_axis, float minor_axis, float rotation) noexcept;
  void setAxes(float mayor, float minor) noexcept;
  bool setPosition(float x, float y) noexcept;
  bool setRotation(float rotation) noexcept;

  void draw(QPaintDevice *painting_area, const QPen &pen, const QRect &roi = QRect()) const;

  inline bool setPosition(const QPointF &point) noexcept {
	return setPosition(point.x(), point.y());
  }

  inline void setAxes(const QPointF &point) noexcept {
	setAxes(point.x(), point.y());
  }

  [[nodiscard]] inline QPointF position() const noexcept {
	return QPointF(x_, y_);
  }

  [[nodiscard]] inline QPointF axes() const noexcept {
	return QPointF(mayor_, minor_);
  }

  [[nodiscard]] inline float rotation() const noexcept {
	return rotation_;
  }
 private:
  float x_, y_, mayor_, minor_, rotation_;
};
}

#endif //WAFT_SRC_MODEL_ELLIPSE_H_
