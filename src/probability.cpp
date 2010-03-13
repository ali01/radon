#include "probability.h"

#include <simone/math.h>

namespace Radon {

Probability::Probability(Frequency num, Frequency den) :
  Simone::Numeric<Probability,double>((double)num.value() / den.value()) {}

bool
Probability::equal(double v) const {
  return Simone::math::equal(value_, v);
}

} /* end of namespace Radon */
