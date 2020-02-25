//
// Created by christopher on 25.02.2020.
//

#ifndef WAFT_SRC_VIEW_ANNOTATIONPAGE_H_
#define WAFT_SRC_VIEW_ANNOTATIONPAGE_H_

#include "../model/Sample.h"
#include <QWizardPage>

namespace waft::view {
class AnnotationWidget;

class AnnotationPage : public QWizardPage {
 Q_OBJECT

 public:
  explicit AnnotationPage(const model::Sample &sample, QWidget *parent = nullptr);
  void setNextId(int id);
  [[nodiscard]] model::Ellipse ellipse() const;

  [[nodiscard]] int nextId() const override;
  void initializePage() override;

 private:
  model::Sample sample_;
  AnnotationWidget *annotation_widget_;
  int next_id_;
};
}

#endif //WAFT_SRC_VIEW_ANNOTATIONPAGE_H_
