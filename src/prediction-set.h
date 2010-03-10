#ifndef PREDICTION_H_DN1M8644
#define PREDICTION_H_DN1M8644

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

namespace Radon {

class PredictionSet : public Simone::PtrInterface<PredictionSet> {
public:
  typedef Simone::Ptr<const PredictionSet> PtrConst;
  typedef Simone::Ptr<PredictionSet> Ptr;

  static Ptr PredictionSetNew() { return new PredictionSet(); }

protected:
  PredictionSet() {}

  /* data members */
  Vector<Prediction::Ptr> prediction_;

private:
  /* disallowed operations */
  PredictionSet(const PredictionSet&);
  void operator=(const PredictionSet&);
};

} /* end of namespace Radon */

#endif
