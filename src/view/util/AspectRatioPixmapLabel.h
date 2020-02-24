//
// Created by Christopher Gundler on 24.02.2020.
//

#ifndef WAFT_SRC_VIEW_UTIL_ASPECTRATIOPIXMAPLABEL_H_
#define WAFT_SRC_VIEW_UTIL_ASPECTRATIOPIXMAPLABEL_H_

#include <QLabel>

namespace waft::view::util {
class AspectRatioPixmapLabel : public QLabel {
 public:
  explicit AspectRatioPixmapLabel(QWidget *parent = nullptr);
  explicit AspectRatioPixmapLabel(const QPixmap &pixmap, QWidget *parent = nullptr);
  [[nodiscard]] int heightForWidth(int width) const override;
  [[nodiscard]] QSize sizeHint() const override;
  void setPixmap(const QPixmap &);
  void resizeEvent(QResizeEvent *) override;

 private:
  [[nodiscard]] QPixmap scaledPixmap() const;

  QPixmap pixmap_;
};
}

#endif //WAFT_SRC_VIEW_UTIL_ASPECTRATIOPIXMAPLABEL_H_
