#include "gradient.h"

namespace Radon {

Gradient::Gradient(size_t _domain_size) {
  /* initialize values of gradient vector using stub value;
     note that the size of the gradient vector is _domain_size + 1 because
     gradient_[0] is reserved for alpha in the expression for z;
     z = B_0 + B_1(x_1) + B_2(x_2) + ... + B_k(x_k) */
  for (size_t i = 0; i < _domain_size + 1; ++i)
    gradient_.pushBack(0.0);
}

} /* end of namespace Radon */