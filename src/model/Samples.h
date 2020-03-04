//
// Created by christopher on 24.02.2020.
//

#ifndef WAFT_SRC_MODEL_SAMPLES_H_
#define WAFT_SRC_MODEL_SAMPLES_H_

#include "Sample.h"

#include <QObject>
#include <QStringList>

namespace waft::model {
class Samples : public QObject {
 Q_OBJECT

 public:
  explicit Samples(QObject *parent = nullptr) : QObject(parent) {};
  virtual bool load() = 0;

  static QStringList supportedFormats();

 signals:
  void loaded(const Sample &sample);
  void failure(const Sample &filename);
  void done();
};
}

#endif //WAFT_SRC_MODEL_SAMPLES_H_
