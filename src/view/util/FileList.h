//
// Created by christopher on 24.02.2020.
//

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
