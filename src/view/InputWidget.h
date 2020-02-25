//
// Created by christopher on 24.02.2020.
//

#ifndef WAFT_SRC_VIEW_INPUTWIDGET_H_
#define WAFT_SRC_VIEW_INPUTWIDGET_H_

#include "../model/Samples.h"

#include <QListWidget>

namespace waft::view {
class InputWidget : public QListWidget {
 Q_OBJECT

 public:
  explicit InputWidget(QWidget *parent = nullptr);
  void dropEvent(QDropEvent *event) override;

  [[nodiscard]] bool isComplete() const;
  model::Samples *samples();

 signals:
  void completeChanged();
  void samplesChanged();

 protected:
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dragEnterEvent(QDragEnterEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;

 private:
  bool _addPath(const QString &path);
  void _deleteCurrent();

  QListWidgetItem *info_item_;
  QStringList supported_format_;
  bool complete_;
};
}

#endif //WAFT_SRC_VIEW_INPUTWIDGET_H_
