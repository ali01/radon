#include "naive-bayes.h"

namespace Radon {

NaiveBayesClassifier::NaiveBayesClassifier(DatasetDescription::Ptr _train_data,
                                           DatasetDescription::Ptr _test_data)
  : train_data_(_train_data), test_data_(_test_data) {}

Prediction::Ptr
NaiveBayesClassifier::prediction(EstimationMode _mode) {
  
}

} /* end of namespace Radon */
