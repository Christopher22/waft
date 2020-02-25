//
// Created by christopher on 24.02.2020.
//

#include "InputWidget.h"
#include "../model/samples/Files.h"

#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QShortcut>
#include <QFileDialog>

namespace waft::view {

InputWidget::InputWidget(QWidget *parent)
	: QListWidget(parent),
	  info_item_(new QListWidgetItem("Please drop files or double click here", this)),
	  supported_format_(model::Samples::supportedFormats()),
	  complete_(false) {
  this->setAcceptDrops(true);
  this->setDragEnabled(true);

  this->setSelectionMode(QAbstractItemView::SingleSelection);
  this->setDropIndicatorShown(true);
  this->setDragDropMode(QAbstractItemView::InternalMove);

  this->setAlternatingRowColors(true);

  // Enable deleting
  auto *shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this, nullptr, nullptr, Qt::WidgetShortcut);
  QObject::connect(shortcut, &QShortcut::activated, this, &InputWidget::_deleteCurrent);
}

bool InputWidget::isComplete() const {
  return complete_;
}

model::Samples *InputWidget::samples() {
  if (!this->isComplete()) {
	return nullptr;
  }

  auto *samples = new model::samples::Files(nullptr);
  samples->reserve(this->count());
  for (int row = 0, size = this->count(); row < size; ++row) {
	samples->append(this->item(row)->data(Qt::UserRole).toString());
  }
  return samples;
}

void InputWidget::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
	event->acceptProposedAction();
  } else {
	QListWidget::dragEnterEvent(event);
  }
}

void InputWidget::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasUrls()) {
	event->acceptProposedAction();
  } else {
	QListWidget::dragMoveEvent(event);
  }
}

void InputWidget::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasUrls()) {
	for (auto &url: event->mimeData()->urls()) {
	  this->_addPath(url.toLocalFile());
	}
	event->acceptProposedAction();
  }
  QListWidget::dropEvent(event);
}

bool InputWidget::_addPath(const QString &path) {
  QFileInfo file_info(path);
  if (!file_info.isFile() || !supported_format_.contains(file_info.suffix(), Qt::CaseInsensitive)) {
	return false;
  }

  // Delete helper information
  if (info_item_ != nullptr) {
	delete info_item_;
	info_item_ = nullptr;
  }

  if (!complete_) {
	complete_ = true;
	emit this->completeChanged();
  }

  auto *item = new QListWidgetItem(file_info.fileName(), this);
  item->setData(Qt::UserRole, path);

  emit this->samplesChanged();
  return true;
}

void InputWidget::_deleteCurrent() {
  auto *current_item = this->currentItem();
  if (current_item == nullptr) {
	return;
  }

  // Handle the info item with special care
  if (current_item->data(Qt::UserRole).isNull()) {
	delete info_item_;
	info_item_ = nullptr;
  } else {
	delete current_item;
  }

  if (complete_ && this->model()->rowCount() == 0) {
	complete_ = false;
	emit this->completeChanged();
  }

  emit this->samplesChanged();
}

void InputWidget::mouseDoubleClickEvent(QMouseEvent *) {
  const QString filter = QString("Frames (*.%1)").arg(supported_format_.join(" *."));
  for (auto &file : QFileDialog::getOpenFileNames(
	  this,
	  "Select one or more frames to open",
	  QString(),
	  filter)) {
	this->_addPath(file);
  }
}

}