//
// Created by christopher on 21.02.2020.
//

#include "FileSelector.h"

#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>

namespace waft::view::util {

FileSelector::FileSelector(QString description, QString filter, bool for_saving, QWidget *parent)
	: QWidget(parent),
	  path_(new QComboBox(this)),
	  description_(std::move(description)),
	  filter_(std::move(filter)),
	  for_saving_(for_saving) {
  path_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  path_->addItem("Please select a file");
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
							QFileDialog::getSaveFileName(this, description_, QString(), filter_) :
							QFileDialog::getOpenFileName(this, description_, QString(), filter_);

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

}