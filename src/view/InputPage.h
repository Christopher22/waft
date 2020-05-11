/*
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef WAFT_SRC_VIEW_INPUTPAGE_H_
#define WAFT_SRC_VIEW_INPUTPAGE_H_

#include "../model/Sample.h"

#include <QWizardPage>

class QThread;

namespace waft::view {
namespace inputs {
class Input;
}

class InputPage : public QWizardPage {
 Q_OBJECT

 public:
  explicit InputPage(QWidget *parent = nullptr);
  ~InputPage() override;

  [[nodiscard]] bool isComplete() const override;
  [[nodiscard]] int nextId() const override;
  void initializePage() override;
  bool validatePage() override;

 signals:
  void _startBackgroundJob();

 private:
  void _loadData();
  void _onDataAvailabilityChanged();
  void _onSamplesChanged();
  void _onLoadedSample(const model::Sample &sample);
  void _onFailedSample(const model::Sample &sample);
  void _onDone();
  void _cleanWorker();

  inputs::Input *main_widget_;
  QThread *worker_;
  QVector<int> annotation_page_indices_;
};
}

#endif //WAFT_SRC_VIEW_INPUTPAGE_H_
