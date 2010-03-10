#include "nb-classifier.h"

#include "nb-prediction-set.h"

namespace Radon {

PredictionSet::PtrConst
NBClassifier::predictionSet(EstMode _mode) {
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = NBPredictionSet::NBPredictionSetNew(_mode);

  if (train_data_ == NULL || test_data_ == NULL)
    return prediction_set_;

  train_algorithm(_mode);
  return compute_prediction_set(_mode);
}


void
NBClassifier::train_algorithm(EstMode _mode) {

}

PredictionSet::PtrConst
NBClassifier::compute_prediction_set(EstMode _mode) {

}

} /* end of namespace Radon */
