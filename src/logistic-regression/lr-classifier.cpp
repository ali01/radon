#include "lr-classifier.h"

#include "gradient-delta.h"

namespace Radon {

LRClassifier::LRClassifier(DatasetDescription::PtrConst _training_data,
                           size_t _domain_size, size_t _range_size,
                           uint32_t _epochs, double _learning_rate) :
  Classifier(_training_data, _domain_size, _range_size),
  beta_(BetaSet::BetaSetNew(_domain_size))
{
  GradientDelta::PtrConst delta;
  for (uint32_t epoch = 0; epoch < _epochs; ++epoch) {
    /* initialize batch gradient for epoch */
    delta = GradientDelta::GradientDeltaNew(training_data_, beta_);

    /* update beta with computed delta */
    beta_->betaInc(delta, _learning_rate);
  }
}

} /* end of namespace Radon */
