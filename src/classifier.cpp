#include "classifier.h"

#include "globals.h"

namespace Radon {

Classifier::Classifier(DatasetDescription::PtrConst _training_data) :
  training_data_(_training_data),
  domain_size_(kDomainSize),
  range_size_(kRangeSize) {}

void
Classifier::testDatasetIs(DatasetDescription::PtrConst _data) {
  if (_data == NULL || test_data_ != _data)
    prediction_set_ = NULL;

  test_data_ = _data;
}

} /* end of namespace Radon */
