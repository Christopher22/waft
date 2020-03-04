//
// Created by christopher on 24.02.2020.
//

#ifndef WAFT_SRC_MODEL_SAMPLES_FILES_H_
#define WAFT_SRC_MODEL_SAMPLES_FILES_H_

#include "../Samples.h"
#include <QStringList>

namespace waft::model::samples {
class Files : public Samples, public QStringList {
 public:
  explicit Files(QObject *parent = nullptr);
  bool load() override;
};
}

#endif //WAFT_SRC_MODEL_SAMPLES_FILES_H_
