#include "probability-ln.h"

#include <cmath>
#include <limits>

#include <simone/math.h>

namespace Radon {

ProbabilityLn::ProbabilityLn(Probability p) {
  if (Simone::math::equal(p.value(), 0.0))
    valueIs(numeric_limits<double>::min());
  else
    valueIs(log(p.value()));
}

bool
ProbabilityLn::equal(double p) const {
  return Simone::math::equal(value_, p);
}

} /* end of namespace Radon */
