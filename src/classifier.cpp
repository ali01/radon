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

/* generates a set of predictions for TEST_DATA (see base class Classifier);
   calls virtual function prediction() which is overriden by derived
   classes */
OutputPredictionSet::PtrConst
Classifier::predictionSet() {
  /* if a prediction set for test_data_ has
     already been computed and is cached, return it */
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = OutputPredictionSet::OutputPredictionSetNew(range_size_);

  /* if test_data_ is NULL, return an empty prediction */
  if (test_data_ == NULL)
    return prediction_set_;

  /* compute prediction set for each input vector in TEST_DATA */
  OutputPrediction::PtrConst pd;
  for (uint32_t vec = 0; vec < test_data_->vectorCount(); ++vec) {
    pd = prediction(test_data_, vec);
    prediction_set_->pushBack(pd);
  }

  return prediction_set_;
}

} /* end of namespace Radon */
