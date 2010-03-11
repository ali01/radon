#ifndef PROBABILITY_H_OHTFUO83
#define PROBABILITY_H_OHTFUO83

#include <simone/numeric.h>

namespace Radon {

class Probability : public Simone::Numeric<Probability,double> {
public:
  Probability() : Simone::Numeric<Probability,double>(1.0) {}
  Probability(double v) : Simone::Numeric<Probability,double>(v) {}
};

} /* end of namespace radon */

#endif
