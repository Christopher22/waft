//
// Created by christopher on 25.02.2020.
//

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
