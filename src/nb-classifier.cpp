#include "nb-classifier.h"

#include "nb-prediction-set.h"

namespace Radon {

PredictionSet::Ptr
NBClassifier::predictionSet(EstMode _mode) {
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = NBPredictionSet::NBPredictionSetNew(_mode);

  if (train_data_ == NULL || test_data_ == NULL)
    return prediction_set_;


}

} /* end of namespace Radon */
