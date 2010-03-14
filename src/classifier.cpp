#include "classifier.h"

namespace Radon {

Classifier::Classifier(DatasetDescription::PtrConst _training_data,
                       size_t _domain_size, size_t _range_size) :
  training_data_(_training_data),
  domain_size_(_domain_size),
  range_size_(_range_size) {}

void
Classifier::testDatasetIs(DatasetDescription::PtrConst _data) {
  if (_data == NULL || test_data_ != _data)
    prediction_set_ = NULL;
  test_data_ = _data;
}

} /* end of namespace Radon */
