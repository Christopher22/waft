//
// Created by christopher on 25.02.2020.
//

#ifndef WAFT_SRC_VIEW_OUTPUTPAGE_H_
#define WAFT_SRC_VIEW_OUTPUTPAGE_H_

#include <QWizardPage>
#include <QVector>

namespace waft::view {
class AnnotationPage;

class OutputPage : public QWizardPage, public QVector<AnnotationPage *> {
 Q_OBJECT

 public:
  explicit OutputPage(QWidget *parent = nullptr);
  [[nodiscard]] int nextId() const override;
};
}

#endif //WAFT_SRC_VIEW_OUTPUTPAGE_H_
