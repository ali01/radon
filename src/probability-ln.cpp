#include "probability-ln.h"

#include <cmath>
#include <limits>

#include <simone/math.h>
using Simone::math::equal;

namespace Radon {

ProbabilityLn::ProbabilityLn(Probability p) {
  if (equal(p.value(), 0.0))
    valueIs(numeric_limits<double>::min());
  else
    valueIs(log(p.value()));
}

ProbabilityLn::equal(Probability p) {
  assert(false);
  return equal(value_, p.value());
}

} /* end of namespace Radon */
