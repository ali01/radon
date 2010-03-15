#ifndef BETA_SET_H_AZLY7D6Z
#define BETA_SET_H_AZLY7D6Z

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "../observation.h"
#include "../dataset-description.h"

namespace Radon {

/* forward declaration */
class GradientDelta;

class BetaSet : public Simone::PtrInterface<BetaSet> {
public:
  typedef Simone::Ptr<const BetaSet> PtrConst;
  typedef Simone::Ptr<BetaSet> Ptr;

  typedef DatasetDescription::Instance DataInstance;

  static Ptr BetaSetNew(size_t _dimensions) {
    return new BetaSet(_dimensions);
  }

  /* increments the beta parameter vector by x, where x is the product of
     its corresponding value in DELTA multiplied by LEARNING_RATE */
  void betaInc(Simone::Ptr<const GradientDelta> _delta, double learning_rate);

  double beta(uint32_t idx) const { return beta_[idx]; }

  /* For the given data instance (input vector) returns the value of z,
     computed with the beta parameters in BETA. Note that the z value in
     the logistic function is known as the logit (courtesy of wikipedia) */
  double logit(DataInstance::PtrConst _instance) const;

private:
  BetaSet(size_t _dimensions);

  /* data members */
  Vector<double> beta_;

  /* disallowed operations */
  BetaSet(const BetaSet&);
  void operator=(const BetaSet&);
};

} /* end of namespace Radon */

#endif
