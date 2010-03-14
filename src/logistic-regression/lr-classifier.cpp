#include "lr-classifier.h"

#include "gradient.h"

namespace Radon {

LRClassifier::LRClassifier(DatasetDescription::PtrConst _training_data,
                           size_t _domain_size, size_t _range_size,
                           uint32_t _epochs) :
  Classifier(_training_data, _domain_size, _range_size),
  beta_(BetaSet::BetaSetNew(_domain_size))
{
  Gradient::PtrConst gradient;
  for (uint32_t epoch = 0; epoch < _epochs; ++epoch) {
    /* initialize batch gradient for epoch */
    gradient = Gradient::GradientNew(training_data_, beta_);
    
  }
}

} /* end of namespace Radon */
