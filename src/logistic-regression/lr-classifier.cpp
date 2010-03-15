#include "lr-classifier.h"

#include "gradient-delta.h"

namespace Radon {

LRClassifier::LRClassifier(DatasetDescription::PtrConst _training_data,
                           uint32_t _epochs, double _learning_rate,
                           double _threshold) :
  Classifier(_training_data, kDomainSize, kRangeSize),
  beta_(BetaSet::BetaSetNew(_training_data->varCount())),
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

/* private member functions */

/* overrides pure virtual function in derived class;
   computes an output prediction for the given input vector INSTANCE */
Observation
LRClassifier::prediction(DataInstance::PtrConst _instance) const {
  double cond_prob;
  Observation prediction;

  /* compute the conditional probability P(Y=1 | X)
     where X is the input vector INSTANCE */
  cond_prob = condProb(Observation(1), _instance);

  /* compute the value of our prediction based on the value of threshold_ */
  prediction = (cond_prob > threshold_) ? Observation(1) : Observation(0);

  return prediction;
}

/* returns the probability P(Y=y | X) where y is the specified observation and
   X is the specified data instance (input vector) */
double
LRClassifier::condProb(const Observation& _out_y,
                       DataInstance::PtrConst _instance) const {
  double e_z = exp(-1 * beta_->logit(_instance));

  /* Set numerator of P appropriately:
     P(Y=1 | X) =  1  / (1 + e_z) whereas
     P(Y=0 | X) = e_z / (1 + e_z) */
  double numerator = (_out_y.value() == 1) ? 1 : e_z;

  /* from the logistic function */
  return numerator / (1 + e_z);
}

} /* end of namespace Radon */
