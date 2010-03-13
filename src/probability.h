#ifndef PROBABILITY_H_OHTFUO83
#define PROBABILITY_H_OHTFUO83

#include <simone/numeric.h>

#include "frequency.h"

namespace Radon {

class Probability : public Simone::Numeric<Probability,double> {
public:
  Probability(double v=1.0) : Simone::Numeric<Probability,double>(v) {}
  Probability(Frequency num, Frequency den);
private:
  bool equal(double v) const;
};

} /* end of namespace radon */

#endif
