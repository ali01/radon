#include "classifier.h"

namespace Radon {

void
Classifier::trainDatasetIs(DatasetDescription::PtrConst _data) {
  if (_data == NULL || train_data_ != _data)
    prediction_set_ = NULL;

  train_data_ = _data;
}

void
Classifier::testDatasetIs(DatasetDescription::PtrConst _data) {
  if (_data == NULL || test_data_ != _data)
    prediction_set_ = NULL;

  test_data_ = _data;
}

} /* end of namespace Radon */
