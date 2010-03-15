#ifndef GRADIENT_H_22KFC3GF
#define GRADIENT_H_22KFC3GF

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "../dataset-description.h"

#include "beta-set.h"

namespace Radon {

class GradientDelta : public Simone::PtrInterface<GradientDelta> {
public:
  typedef Simone::Ptr<const GradientDelta> PtrConst;

  static PtrConst GradientDeltaNew(DatasetDescription::PtrConst _dataset,
                                   BetaSet::PtrConst _beta_set) {
    return new GradientDelta(_dataset, _beta_set);
  }

  size_t size() const { return gradient_.size(); }
  double element(uint32_t _i) const { return gradient_[_i]; }

private:
  typedef DatasetDescription::Instance DataInstance;

  GradientDelta(DatasetDescription::PtrConst _dataset,
                BetaSet::PtrConst _beta_set);

  /* static functions */
  static double
  gradient_delta(DataInstance::PtrConst _instance, BetaSet::PtrConst _beta_set,
                 Observation _in_x, Observation _out_y);

  /* data members */
  Vector<double> gradient_;

  /* disallowed operations */
  GradientDelta(const GradientDelta&);
  void operator=(const GradientDelta&);
};

} /* end of namespace Radon */

#endif
