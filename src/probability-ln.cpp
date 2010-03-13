#include "probability-ln.h"

#include <cmath>
#include <limits>

#include <simone/math.h>

namespace Radon {

ProbabilityLn::ProbabilityLn(Probability p) {
  if (Simone::math::equal(p.value(), 0.0)){
    /* numeric_limits<double>::min() is equal to zero; use negative max */
    valueIs(-1 * numeric_limits<double>::max());
  } else {
    valueIs(log(p.value()));
  }
}

bool
ProbabilityLn::equal(double p) const {
  return Simone::math::equal(value_, p);
}

} /* end of namespace Radon */
