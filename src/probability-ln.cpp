#include "probability-ln.h"

#include <cmath>
#include <limits>

namespace Radon {

ProbabilityLn::ProbabilityLn(Probability p) {
  if (p == 0)
    valueIs(numeric_limits<double>::min());
  else
    valueIs(log(p.value()));
}

} /* end of namespace Radon */
