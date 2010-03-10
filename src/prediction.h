#ifndef PREDICTION_H_XPYR6044
#define PREDICTION_H_XPYR6044

#include <simone/ptr_interface.h>

namespace Radon {

class Prediction : Simone::PtrInterface<Prediction> {
public:
  typedef Simone::Ptr<const Prediction> PtrConst;
  typedef Simone::Ptr<Prediction> Ptr;

  static Ptr PredictionNew() { return new Prediction(); }

private:

  /* disallowed operations */
  Prediction(const Prediction&);
  void operator=(const Prediction&);
};

} /* end of namespace Radon */

#endif
