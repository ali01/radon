#include "beta-set.h"

#include <cmath>

#include <simone/exception.h>

#include "gradient-delta.h"

namespace Radon {

BetaSet::BetaSet(size_t _domain_size) {
  /* initialize values of beta-set vector to zero;
     note that the size of the beta-set vector is _domain_size + 1 because
     beta_[0] is reserved for alpha in the expression for z;
     z = B_0 + B_1(x_1) + B_2(x_2) + ... + B_k(x_k) */
  for (size_t i = 0; i < _domain_size + 1; ++i)
    beta_.pushBack(0.0);
}

/* increments the beta parameter vector by x, where x is the product of
   its corresponding value in DELTA multiplied by LEARNING_RATE */
void
BetaSet::betaInc(GradientDelta::PtrConst _delta, double learning_rate) {
  if (beta_.size() != _delta->size()) {
    string msg = "beta vector and gradient delta size mismatch";
    throw Simone::RangeException(__FILE__, __LINE__, msg);
  }

  for (size_t i = 0; i < beta_.size(); ++i)
    beta_[i] = learning_rate * _delta->element(i);
}

/* returns the probability P(Y=y, X) where y is the specified observation and
   X is the specified data instance (input vector) */
double
BetaSet::condProb(const Observation& _out_y, DataInstance::PtrConst _instance) {
  double e_z = exp(-1 * logit(_instance));

  /* Set numerator of P appropriately:
     P(Y=1 | X) =  1  / (1 + e_z) whereas
     P(Y=0 | X) = e_z / (1 + e_z) */
  double numerator = (_out_y.value() == 1) ? 1 : e_z;

  /* from the logistic function */
  return numerator / (1 + e_z);
}

double
BetaSet::logit(DataInstance::PtrConst _instance) const {
  if (beta_.size() != _instance->size()){
    string msg = "beta vector and instance size mismatch.";
    throw Simone::RangeException(__FILE__, __LINE__, msg);
  }

  /* incrementally compute the value of z, given by:
     z = B_0(x_0=1) + B_1(x_1) + B_2(x_2) + ... + B_k(x_k) */
  double x_i, z = 0.0;
  for (size_t i = 0; i < _instance->size(); ++i) {
    x_i = _instance->element(i).value();
    z += x_i * beta_[i];
  }

  return z;
}

} /* end of namespace Radon */
