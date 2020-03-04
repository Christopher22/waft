//
// Created by christopher on 04.03.2020.
//

#ifndef WAFT_SRC_VIEW_INPUTS_IMAGES_H_
#define WAFT_SRC_VIEW_INPUTS_IMAGES_H_

#include "Input.h"

namespace waft::view {
namespace util {
class FileList;
}

namespace inputs {
class Images : public Input {
 public:
  explicit Images(QWidget *widget = nullptr);
  [[nodiscard]] QString inputName() const override;
  [[nodiscard]] bool isReady() const override;
  model::Samples *samples() override;

 private:
  util::FileList *images_;
};
}
}

#endif //WAFT_SRC_VIEW_INPUTS_IMAGES_H_
