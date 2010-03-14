#ifndef GRADIENT_H_22KFC3GF
#define GRADIENT_H_22KFC3GF

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "../dataset-description.h"

#include "beta-set.h"

namespace Radon {

class Gradient : public Simone::PtrInterface<Gradient> {
public:
  typedef Simone::Ptr<const Gradient> PtrConst;

  static PtrConst GradientNew(DatasetDescription::PtrConst _dataset,
                              BetaSet::PtrConst _beta_set) {
    return new Gradient(_dataset, _beta_set);
  }

  double operator[](const uint32_t& _i) const { return gradient_[_i]; }

private:
  typedef DatasetDescription::Instance DataInstance;

  Gradient(DatasetDescription::PtrConst _dataset, BetaSet::PtrConst _beta_set);

  /* member functions */

  DataInstance::PtrConst
  data_instance(DatasetDescription::PtrConst _dataset, uint32_t idx) const;

  /* static functions */

  static double
  gradient_delta(DataInstance::PtrConst _instance, BetaSet::PtrConst _beta_set,
                 Observation _in_x, Observation _out_y);

  /* data members */
  Vector<double> gradient_;

  /* disallowed operations */
  Gradient(const Gradient&);
  void operator=(const Gradient&);
};

} /* end of namespace Radon */

#endif
