#include "nb-classifier.h"

#include "globals.h"
#include "nb-prediction-set.h"

namespace Radon {

NBClassifier::NBClassifier(DatasetDescription::PtrConst training_data) :
  Classifier(training_data)
{
  
}

PredictionSet::PtrConst
NBClassifier::predictionSet(EstMode _mode) {
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = NBPredictionSet::NBPredictionSetNew(_mode);

  if (test_data_ == NULL)
    return prediction_set_;

  return compute_prediction_set(_mode);
}


PredictionSet::PtrConst
NBClassifier::compute_prediction_set(EstMode _mode) {

}

} /* end of namespace Radon */
