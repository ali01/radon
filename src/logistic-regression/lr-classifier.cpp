#include "lr-classifier.h"

#include "gradient.h"

namespace Radon {

LRClassifier::LRClassifier(DatasetDescription::PtrConst _training_data,
                           size_t _domain_size, size_t _range_size,
                           uint32_t _epochs) :
  Classifier(_training_data, _domain_size, _range_size),
  beta_(BetaSet::BetaSetNew(_domain_size))
{
  Gradient::Ptr gradient;
  DataInstance::PtrConst data_instance;
  for (uint32_t epoch = 0; epoch < _epochs; ++epoch) {
    /* initialize batch gradient for epoch */
    gradient = Gradient::GradientNew(_domain_size);

    /* iterate over each data instance (input vector) in the training dataset,
       and add it's contribution to the gradient vector */
    for (uint32_t vec = 0; vec < _training_data->vectorCount(); ++vec) {
      /* data instance with x_0 = 1 (x_0 is paired with alpha in z) */
      data_instance = dataInstance(_training_data, vec);

      /* iterate over each observation in the instance vector and add its
         individual contribution to the batch gradient using the gradient
         equation for the log conditional likelihood of the data:
         G = x_j(y - 1 / (1 + e^{-z}))
           = x_j(y - P(Y=1 | X)) */
      for (size_t var = 0; var < data_instance->size(); ++var) {
        // gradient[var] +=
      }
    }
  }
}

LRClassifier::DataInstance::PtrConst
LRClassifier::dataInstance(DatasetDescription::PtrConst _dataset,
                           uint32_t idx) {
  DataInstance::PtrConst instance_const = _dataset->instance(idx);

  /* note that, for the purpose of logistic regression, the length of a data
     instance vector is equal to the size of the domain plus one; the first
     value of the vector is always 1 and is there to pair up with alpha in
     the expression for z (which appears in the logistic function) */

  /* const_cast the data instance and push 1 as the first observation */
  DataInstance::Ptr instance = const_cast<DataInstance *>(instance_const.ptr());
  instance->pushFront(Observation(1));

  /* version returned is PtrConst, as it should never again be modified */
  return instance_const;
}

} /* end of namespace Radon */
