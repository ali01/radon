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
  Vector<Observation>::PtrConst lr_input_vector;
  for (uint32_t epoch = 0; epoch < _epochs; ++epoch) {
    /* initialize batch gradient for epoch */
    gradient = Gradient::GradientNew(_domain_size);

    /* iterate over each input vector in the training dataset,
       and add it's contribution to the gradient vector */
    for (uint32_t vec = 0; vec < _training_data->vectorCount(); ++vec) {
      // lr_input_vector =
    }
  }
}

LRClassifier::DataInstance::PtrConst
LRClassifier::dataInstance(DatasetDescription::PtrConst _dataset,
                           uint32_t idx) {
  // DataInstance instance_const = _dataset->instance(idx);
  // DataInstance instance = const_cast<
}

} /* end of namespace Radon */
