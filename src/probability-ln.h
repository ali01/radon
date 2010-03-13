#ifndef PROBABILITY_LN_H_3AWNZU0T
#define PROBABILITY_LN_H_3AWNZU0T

#include <cmath>

#include <simone/numeric.h>

#include "probability.h"

namespace Radon {

class ProbabilityLn : public Simone::Numeric<ProbabilityLn,double> {
public:
  ProbabilityLn(Probability p);
};

} /* end of namespace Radon */

#endif
