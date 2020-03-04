//
// Created by christopher on 04.03.2020.
//

#ifndef WAFT_SRC_VIEW_UTIL_ASPECTRATIOWIDGET_H_
#define WAFT_SRC_VIEW_UTIL_ASPECTRATIOWIDGET_H_

#include <QWidget>

class QBoxLayout;
namespace waft::view::util {

class AspectRatioWidget : public QWidget {
 public:
  explicit AspectRatioWidget(QWidget *widget, QWidget *parent = nullptr);
  void resizeEvent(QResizeEvent *event) override;

  inline QWidget *child() noexcept {
	return child_;
  };
  
 private:
  QBoxLayout *layout;
  QWidget *child_;
  float aspect_ratio_;
};
}
#endif //WAFT_SRC_VIEW_UTIL_ASPECTRATIOWIDGET_H_
