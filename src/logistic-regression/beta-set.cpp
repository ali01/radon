#include "beta-set.h"

namespace Radon {

BetaSet::BetaSet(size_t _domain_size) {
  /* initialize values of beta-set vector to zero;
     note that the size of the beta-set vector is _domain_size + 1 because
     beta_[0] is reserved for alpha in the expression for z;
     z = B_0 + B_1(x_1) + B_2(x_2) + ... + B_k(x_k) */
  for (size_t i = 0; i < _domain_size + 1; ++i)
    beta_.pushBack(0.0);
}

} /* end of namespace Radon */