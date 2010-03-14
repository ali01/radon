#include "lr-classifier.h"

namespace Radon {

LRClassifier::LRClassifier(DatasetDescription::PtrConst training_data,
                           size_t _domain_size, size_t _range_size) :
  Classifier(training_data, _domain_size, _range_size),
  beta_(BetaSet::BetaSetNew(_domain_size)),
  gradient_(Gradient::GradientNew(_domain_size))
{

}

} /* end of namespace Radon */
