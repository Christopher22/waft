/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_ANNOTATIONPAGE_H_
#define WAFT_SRC_VIEW_ANNOTATIONPAGE_H_

#include "../model/Sample.h"
#include <QWizardPage>

class QCheckBox;

namespace waft::view {
class AnnotationWidget;
class AnnotationPage : public QWizardPage {
 Q_OBJECT

 public:
  explicit AnnotationPage(const model::Sample &sample, int annotation_index, QWidget *parent = nullptr);
  void setNextId(int id);
  [[nodiscard]] const model::Sample &sample() const;

  [[nodiscard]] int nextId() const override;
  void initializePage() override;
  void cleanupPage() override;
  bool validatePage() override;

 private:
  QCheckBox *checkbox() noexcept;
  void _cleanUp();
  void _prepare();

  AnnotationWidget *annotation_widget_;
  int next_id_, annotation_index_;
};
}

#endif //WAFT_SRC_VIEW_ANNOTATIONPAGE_H_
