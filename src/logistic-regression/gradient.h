#ifndef GRADIENT_H_22KFC3GF
#define GRADIENT_H_22KFC3GF

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

namespace Radon {

class Gradient : public Simone::PtrInterface<Gradient> {
public:
  typedef Simone::Ptr<const Gradient> PtrConst;
  typedef Simone::Ptr<Gradient> Ptr;

  static Ptr GradientNew(size_t _domain_size) {
    return new Gradient(_domain_size);
  }

private:
  Gradient(size_t _domain_size);

  /* data members */
  Vector<double> gradient_;

  /* disallowed operations */
  Gradient(const Gradient&);
  void operator=(const Gradient&);
};


} /* end of namespace Radon */

#endif
