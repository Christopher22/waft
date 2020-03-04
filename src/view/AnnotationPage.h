//
// Created by christopher on 25.02.2020.
//

#ifndef WAFT_SRC_VIEW_ANNOTATIONPAGE_H_
#define WAFT_SRC_VIEW_ANNOTATIONPAGE_H_

#include "../model/Sample.h"
#include <QWizardPage>

namespace waft::view {
namespace util {
class AspectRatioWidget;
}

class AnnotationWidget;
class AnnotationPage : public QWizardPage {
 Q_OBJECT

 public:
  explicit AnnotationPage(const model::Sample &sample, QWidget *parent = nullptr);
  void setNextId(int id);
  [[nodiscard]] const model::Sample &sample() const;

  [[nodiscard]] int nextId() const override;
  void initializePage() override;

 private:
  model::Sample sample_;
  util::AspectRatioWidget *annotation_widget_;
  int next_id_;
};
}

#endif //WAFT_SRC_VIEW_ANNOTATIONPAGE_H_
