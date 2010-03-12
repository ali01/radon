#include "probability.h"

namespace Radon {

Probability::Probability(Frequency num, Frequency den) :
  Simone::Numeric<Probability,double>((double)num.value() / den.value()) {}

} /* end of namespace Radon */
