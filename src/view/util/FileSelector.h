/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ROIWIZ_SRC_VIEW_UTIL_FILESELECTOR_H_
#define ROIWIZ_SRC_VIEW_UTIL_FILESELECTOR_H_

#include <QWidget>
#include <QFileDialog>

class QComboBox;

namespace waft::view::util {
class FileSelector : public QWidget {
 Q_OBJECT

 public:
  Q_PROPERTY(QString path
				 READ
					 path
				 WRITE
					 setPath
				 NOTIFY
				 pathSelected)

  FileSelector(QString description,
			   QString filter,
			   bool for_saving = false,
			   QString root = QString(),
			   QWidget *parent = nullptr);
  [[nodiscard]] QString path() const;
  void setPath(const QString &path);
  void setRoot(const QString &root);
  explicit operator bool() const;
  QFileDialog::Options *operator->();

 signals:
  void pathSelected(const QString &path);

 protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dropEvent(QDropEvent *event) override;

 private:
  void _selectPath();
  void _onSelectionChange(int index);

  QComboBox *path_;
  QString root_dir_;
  const QString description_, filter_;
  const bool for_saving_;
  QFileDialog::Options options_;
};
}

#endif //ROIWIZ_SRC_VIEW_UTIL_FILESELECTOR_H_
