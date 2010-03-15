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

/* overrides pure virtual function in derived class;
   computes an output prediction for the given INPUT_VECTOR in DATASET */
OutputPrediction::PtrConst
LRClassifier::prediction(DatasetDescription::PtrConst _dataset,
                         uint32_t _input_vector) const {
  double cond_prob;
  Observation pd_value;
  OutputPrediction::PtrConst pd;
  DataInstance::PtrConst instance = data_instance(_dataset, _input_vector);

  /* compute the conditional probability P(Y=1 | X)
     where X is the input vector INSTANCE */
  cond_prob = condProb(Observation(1), instance);

  /* compute the value of our prediction based on the value of threshold_ */
  pd_value = (cond_prob > threshold_) ? Observation(1) : Observation(0);

  pd = OutputPrediction::OutputPredictionNew(_dataset, _input_vector, pd_value);

  return pd;
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
