/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_INPUTIMAGEWIDGET_H_
#define WAFT_SRC_VIEW_INPUTIMAGEWIDGET_H_

#include <QListWidget>

namespace waft::view::util {
class FileList : public QListWidget {
 Q_OBJECT

 public:
  explicit FileList(QStringList supported_formats, QWidget *parent = nullptr);
  void dropEvent(QDropEvent *event) override;
  [[nodiscard]] bool filesAvailable() const;

 protected:
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dragEnterEvent(QDragEnterEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;

 signals:
  void fileAvailabilityChanged();
  void filesChanged();

 private:
  bool _addPath(const QString &path);
  void _deleteCurrent();

  QListWidgetItem *info_item_;
  QStringList supported_format_;
  bool images_available_;
};
}

#endif //WAFT_SRC_VIEW_INPUTIMAGEWIDGET_H_
