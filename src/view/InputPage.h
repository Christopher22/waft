//
// Created by christopher on 25.02.2020.
//

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
