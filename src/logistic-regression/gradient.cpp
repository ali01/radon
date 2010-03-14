#include "gradient.h"

namespace Radon {

Gradient::Gradient(DatasetDescription::PtrConst _dataset,
                   BetaSet::PtrConst _beta_set) {
  /* initialize values of gradient vector using stub value;
     note that the size of the gradient vector is |X| + 1 because
     gradient_[0] is reserved for alpha in the expression for z;
     z = B_0 + B_1(x_1) + B_2(x_2) + ... + B_k(x_k) */
  for (size_t i = 0; i < _dataset->varCount() + 1; ++i)
    gradient_.pushBack(0.0);

  /* iterate over each data instance (input vector) in the training dataset,
     and add it's contribution to the gradient vector */
  DataInstance::PtrConst data_instance;
  for (uint32_t vec = 0; vec < _dataset->vectorCount(); ++vec) {
    /* data instance with x_0 = 1 (x_0 is paired with alpha in z) */
    data_instance = dataInstance(_dataset, vec);

    /* iterate over each observation in the instance vector and add its
       individual contribution to the batch gradient using the gradient
       equation for the log conditional likelihood of the data:
       G = x_j(y - 1 / (1 + e^{-z}))
         = x_j(y - P(Y=1 | X)) */
    for (size_t var = 0; var < data_instance->size(); ++var) {

    }
  }
}

Gradient::DataInstance::PtrConst
Gradient::dataInstance(DatasetDescription::PtrConst _dataset, uint32_t idx) {
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

} /* end of namespace Radon */
