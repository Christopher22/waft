/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_OUTPUTPAGE_H_
#define WAFT_SRC_VIEW_OUTPUTPAGE_H_

#include <QWizardPage>
#include <QVector>

class QCheckBox;
namespace waft::view {
class AnnotationPage;
namespace util {
class FileSelector;
}

class OutputPage : public QWizardPage, public QVector<AnnotationPage *> {
 Q_OBJECT

 public:
  explicit OutputPage(QWidget *parent = nullptr);
  bool validatePage() override;
  [[nodiscard]] int nextId() const override;
  void initializePage() override;

 private:
  util::FileSelector *file_;
  QCheckBox *include_excluded_;
};
}

#endif //WAFT_SRC_VIEW_OUTPUTPAGE_H_
