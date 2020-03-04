//
// Created by christopher on 04.03.2020.
//

#ifndef WAFT_SRC_VIEW_INPUTTSVWIDGET_H_
#define WAFT_SRC_VIEW_INPUTTSVWIDGET_H_

#include "Input.h"

namespace waft {
namespace model {
class Samples;
}

namespace view {
namespace util {
class FileSelector;
}

namespace inputs {
class Tsv : public Input {
 public:
  explicit Tsv(QWidget *parent = nullptr);
  [[nodiscard]] bool isReady() const override;
  [[nodiscard]] QString inputName() const override;
  model::Samples *samples() override;

 private:
  util::FileSelector *selector_;
};
}
}
}

#endif //WAFT_SRC_VIEW_INPUTTSVWIDGET_H_
