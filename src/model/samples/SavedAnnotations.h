//
// Created by christopher on 02.03.2020.
//

#ifndef WAFT_SRC_MODEL_SAMPLES_SAVEDANNOTATIONS_H_
#define WAFT_SRC_MODEL_SAMPLES_SAVEDANNOTATIONS_H_

#include "../Samples.h"

namespace waft::model::samples {
class SavedAnnotations : public Samples {
 public:
  explicit SavedAnnotations(const QString &file, QObject *parent = nullptr);
  bool load() override;

 private:
  QFile file_;
};
}

#endif //WAFT_SRC_MODEL_SAMPLES_SAVEDANNOTATIONS_H_
