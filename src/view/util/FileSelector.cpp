/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "FileSelector.h"

#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>

namespace waft::view::util {

FileSelector::FileSelector(QString description, QString filter, bool for_saving, QString root, QWidget *parent)
	: QWidget(parent),
	  path_(new QComboBox(this)),
	  root_dir_(std::move(root)),
	  description_(std::move(description)),
	  filter_(std::move(filter)),
	  for_saving_(for_saving) {

  this->setAcceptDrops(true);

  path_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  path_->addItem(tr("Please select a file"));
  QObject::connect(path_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FileSelector::_onSelectionChange);

  auto *selector = new QPushButton(this);
  selector->setText("...");
  selector->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  QObject::connect(selector, &QPushButton::clicked, this, &FileSelector::_selectPath);

  auto *layout = new QHBoxLayout(this);
  layout->addWidget(path_);
  layout->addWidget(selector);
  layout->setMargin(0);
  this->setLayout(layout);
}

void FileSelector::_selectPath() {
  const QString file_name = for_saving_ ?
							QFileDialog::getSaveFileName(this, description_, root_dir_, filter_, nullptr, options_) :
							QFileDialog::getOpenFileName(this, description_, root_dir_, filter_, nullptr, options_);

  if (file_name.isEmpty()) {
	return;
  }

  this->setPath(file_name);
}

void FileSelector::_onSelectionChange(int index) {
  QVariant data = path_->itemData(index);
  if (data.isValid()) {
	emit pathSelected(data.toString());
  }
}

FileSelector::operator bool() const {
  return path_->itemData(path_->currentIndex()).isValid();
}

QString FileSelector::path() const {
  return path_->itemData(path_->currentIndex()).toString();
}

void FileSelector::setPath(const QString &path) {
  if (path_->itemData(path_->currentIndex()).isNull()) {
	path_->clear();
  }

  QFileInfo info(path);
  path_->addItem(info.fileName(), path);
  path_->setCurrentIndex(path_->count() - 1);
}

void FileSelector::setRoot(const QString &root) {
  root_dir_ = root;
}

QFileDialog::Options *FileSelector::operator->() {
  return &options_;
}

void FileSelector::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
	event->acceptProposedAction();
  }
}

void FileSelector::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasUrls()) {
	const auto urls = event->mimeData()->urls();
	if (urls.size() == 1) {
	  const QFileInfo local_file(urls[0].toLocalFile());
	  if (local_file.isFile()) {
		this->setPath(local_file.absoluteFilePath());
		event->acceptProposedAction();
	  }
	}
  }
}

}