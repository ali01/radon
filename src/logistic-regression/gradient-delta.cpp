#include "gradient-delta.h"
#include <cmath>

#include "lr-classifier.h"

namespace Radon {

GradientDelta::GradientDelta(DatasetDescription::PtrConst _dataset,
                             BetaSet::PtrConst _beta_set) {
  /* initialize values of gradient vector using stub value;
     note that the size of the gradient vector is |X| + 1 because
     gradient_[0] is reserved for alpha in the expression for z;
     z = B_0 + B_1(x_1) + B_2(x_2) + ... + B_k(x_k) */
  for (size_t i = 0; i < _dataset->varCount() + 1; ++i)
    gradient_.pushBack(0.0);

  /* iterate over each data instance (input vector) in the training dataset,
     and add it's contribution to the gradient vector */
  DataInstance::PtrConst instance;
  Observation in_x, out_y;
  for (uint32_t vec = 0; vec < _dataset->vectorCount(); ++vec) {
    /* data instance with x_0 = 1 (x_0 is paired with alpha in z) */
    instance = LRClassifier::data_instance(_dataset, vec);

    /* iterate over each observation in the instance vector and add its
       individual contribution to the batch gradient using the gradient
       equation for the log conditional likelihood of the data:
       G = x_j(y - 1 / (1 + e^{-z}))
         = x_j(y - P(Y=1 | X)) */
    for (size_t var = 0; var < instance->size(); ++var) {
      in_x = _dataset->inputObservation(vec, var);
      out_y = _dataset->outputObservation(vec);
      gradient_[var] += gradient_delta(instance, _beta_set, in_x, out_y);
    }
  }
}

/* returns a gradient delta for the given input vector,
   set of beta parameters, and values of X and Y */
double
GradientDelta::gradient_delta(DataInstance::PtrConst _instance,
                              BetaSet::PtrConst _beta_set,
                              Observation _in_x, Observation _out_y) {
  double x = static_cast<double>(_in_x.value());
  double y = static_cast<double>(_out_y.value());

  /* compute the value of z */
  double logit = _beta_set->logit(_instance);

  /* compute P(Y=1 | X) */
  double lf = 1 / (1 + exp(-1 * logit));

  return x * (y - lf);
}

} /* end of namespace Radon */