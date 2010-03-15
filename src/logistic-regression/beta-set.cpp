#include "beta-set.h"

#include <cmath>

#include <simone/exception.h>

#include "gradient-delta.h"

namespace Radon {

BetaSet::BetaSet(size_t _dimensions) : intercept_(0.0) {
  /* initialize values of beta-set vector to zero; */
  for (size_t i = 0; i < _dimensions; ++i)
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
    beta_[i] += learning_rate * _delta->component(i);
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

  return intercept_ + z;
}

} /* end of namespace Radon */
