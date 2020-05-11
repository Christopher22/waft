/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "FileList.h"

#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QShortcut>
#include <QFileDialog>

namespace waft::view::util {

FileList::FileList(QStringList supported_formats, QWidget *parent)
	: QListWidget(parent),
	  info_item_(new QListWidgetItem(tr("Please drop files or double click here for a selection"), this)),
	  supported_format_(std::move(supported_formats)),
	  images_available_(false) {
  this->setAcceptDrops(true);
  this->setDragEnabled(true);
  this->setSelectionMode(QAbstractItemView::SingleSelection);
  this->setDropIndicatorShown(true);
  this->setDragDropMode(QAbstractItemView::InternalMove);
  this->setAlternatingRowColors(true);

  // Disable selection of helper
  info_item_->setFlags(Qt::ItemNeverHasChildren);

  // Enable deleting
  auto *shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this, nullptr, nullptr, Qt::WidgetShortcut);
  QObject::connect(shortcut, &QShortcut::activated, this, &FileList::_deleteCurrent);
}

void FileList::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
	event->acceptProposedAction();
  } else {
	QListWidget::dragEnterEvent(event);
  }
}

void FileList::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasUrls()) {
	event->acceptProposedAction();
  } else {
	QListWidget::dragMoveEvent(event);
  }
}

void FileList::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasUrls()) {
	for (auto &url: event->mimeData()->urls()) {
	  this->_addPath(url.toLocalFile());
	}
	event->acceptProposedAction();
  }
  QListWidget::dropEvent(event);
}

bool FileList::_addPath(const QString &path) {
  QFileInfo file_info(path);
  if (!file_info.isFile() || !supported_format_.contains(file_info.suffix(), Qt::CaseInsensitive)) {
	return false;
  }

  // Delete helper information
  if (info_item_ != nullptr) {
	delete info_item_;
	info_item_ = nullptr;
  }

  if (!images_available_) {
	images_available_ = true;
	emit this->fileAvailabilityChanged();
  }

  auto *item = new QListWidgetItem(file_info.fileName(), this);
  item->setData(Qt::UserRole, path);

  emit this->filesChanged();
  return true;
}

void FileList::_deleteCurrent() {
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

  if (images_available_ && this->model()->rowCount() == 0) {
	images_available_ = false;
	emit this->fileAvailabilityChanged();
  }

  emit this->filesChanged();
}

void FileList::mouseDoubleClickEvent(QMouseEvent *) {
  const QString filter = QString("Supported files (*.%1)").arg(supported_format_.join(" *."));
  for (auto &file : QFileDialog::getOpenFileNames(
	  this,
	  "Select one or more files to open",
	  QString(),
	  filter)) {
	this->_addPath(file);
  }
}

bool FileList::filesAvailable() const {
  return images_available_;
}

}