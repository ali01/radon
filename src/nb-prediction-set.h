#ifndef NB_PREDICTION_H_ILM1M24Q
#define NB_PREDICTION_H_ILM1M24Q

#include "prediction-set.h"

namespace Radon {

class NBPredictionSet : public PredictionSet {
public:
  typedef Simone::Ptr<const NBPredictionSet> PtrConst;
  typedef Simone::Ptr<NBPredictionSet> Ptr;

  static Ptr NBPredictionSetNew() { return new NBPredictionSet(); }

private:
  NBPredictionSet() {}

  /* disallowed operations */
  NBPredictionSet(const NBPredictionSet&);
  void operator=(const NBPredictionSet&);
};

} /* end of namespace Radon */

#endif
