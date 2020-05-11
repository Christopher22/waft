/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
