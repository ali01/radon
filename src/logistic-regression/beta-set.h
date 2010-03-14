#ifndef BETA_SET_H_AZLY7D6Z
#define BETA_SET_H_AZLY7D6Z

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "../dataset-description.h"

namespace Radon {

class BetaSet : public Simone::PtrInterface<BetaSet> {
public:
  typedef Simone::Ptr<const BetaSet> PtrConst;
  typedef Simone::Ptr<BetaSet> Ptr;

  typedef DatasetDescription::Instance DataInstance;

  static Ptr BetaSetNew(size_t _domain_size) {
    return new BetaSet(_domain_size);
  }

  double logit(DataInstance::PtrConst _instance) const;

private:
  BetaSet(size_t _domain_size);

  /* data members */
  Vector<double> beta_;

  /* disallowed operations */
  BetaSet(const BetaSet&);
  void operator=(const BetaSet&);
};

} /* end of namespace Radon */

#endif
