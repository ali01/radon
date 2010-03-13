#ifndef PROBABILITY_LN_H_3AWNZU0T
#define PROBABILITY_LN_H_3AWNZU0T

#include <cmath>

#include <simone/numeric.h>

#include "probability.h"

namespace Radon {

class ProbabilityLn : public Simone::Numeric<ProbabilityLn,double> {
public:
  ProbabilityLn(Probability p=Probability(1.0));
};

} /* end of namespace Radon */

#endif
