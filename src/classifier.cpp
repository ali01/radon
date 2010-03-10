#include "classifier.h"

namespace Radon {

Classifier::Classifier(DatasetDescription::PtrConst training_data) :
  training_data_(training_data_) {}

void
Classifier::testDatasetIs(DatasetDescription::PtrConst _data) {
  if (_data == NULL || test_data_ != _data)
    prediction_set_ = NULL;

  test_data_ = _data;
}

} /* end of namespace Radon */
