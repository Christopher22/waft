//
// Created by christopher on 25.02.2020.
//

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
