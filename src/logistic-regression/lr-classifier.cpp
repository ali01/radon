#include "lr-classifier.h"

#include "gradient-delta.h"

namespace Radon {

LRClassifier::LRClassifier(DatasetDescription::PtrConst _training_data,
                           size_t _domain_size, size_t _range_size,
                           uint32_t _epochs, double _learning_rate,
                           double _threshold) :
  Classifier(_training_data, _domain_size, _range_size),
  beta_(BetaSet::BetaSetNew(_domain_size)),
  threshold_(_threshold)
{
  GradientDelta::PtrConst delta;
  for (uint32_t epoch = 0; epoch < _epochs; ++epoch) {
    /* initialize batch gradient for epoch */
    delta = GradientDelta::GradientDeltaNew(training_data_, beta_);

    /* update beta with computed delta */
    beta_->betaInc(delta, _learning_rate);
  }
}

OutputPredictionSet::PtrConst
LRClassifier::predictionSet() {
  /* if a prediction set for test_data_ has
     already been computed and is cached, return it */
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = OutputPredictionSet::OutputPredictionSetNew(range_size_);

  /* if test_data_ is NULL, return an empty prediction */
  if (test_data_ == NULL)
    return prediction_set_;

  // TODO
}

/* static public functions */

/* returns a data instance (that is, a vector of data points or observations)
   that corresponds to the input vector at index IDX in DATASET */
LRClassifier::DataInstance::PtrConst
LRClassifier::data_instance(DatasetDescription::PtrConst _dataset,
                            uint32_t idx) {
  DataInstance::PtrConst instance_const = _dataset->instance(idx);

  /* note that, for the purpose of logistic regression, the length of a data
     instance vector is equal to |X| plus one; the first value of the vector is
     always 1 and is there to pair up with alpha in the expression for z (which
     appears in the logistic function) */

  /* const_cast the data instance and push 1 as the first observation */
  DataInstance::Ptr instance = const_cast<DataInstance *>(instance_const.ptr());
  instance->pushFront(Observation(1));

  /* version returned is PtrConst, as it should never again be modified */
  return instance_const;
}

/* private member functions */

/* returns a prediction for the specified data instance (input vector) */
OutputPrediction::PtrConst
LRClassifier::prediction(DataInstance::PtrConst _instance) {
  double cond_prob = condProb(Observation(1), _instance);
  // TODO
}

/* returns the probability P(Y=y, X) where y is the specified observation and
   X is the specified data instance (input vector) */
double
LRClassifier::condProb(const Observation& _out_y,
                       DataInstance::PtrConst _instance) {
  double e_z = exp(-1 * beta_->logit(_instance));

  /* Set numerator of P appropriately:
     P(Y=1 | X) =  1  / (1 + e_z) whereas
     P(Y=0 | X) = e_z / (1 + e_z) */
  double numerator = (_out_y.value() == 1) ? 1 : e_z;

  /* from the logistic function */
  return numerator / (1 + e_z);
}

} /* end of namespace Radon */
