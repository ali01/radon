#include "probability-ln.h"

namespace Radon {

ProbabilityLn::ProbabilityLn(Probability p) :
  Simone::Numeric<ProbabilityLn,double>(log(p.value())) {}

} /* end of namespace Radon */
