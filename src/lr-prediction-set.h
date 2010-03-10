#ifndef LR_PREDICTION_H_4B7HNQW9
#define LR_PREDICTION_H_4B7HNQW9

#include "prediction-set.h"

namespace Radon {

class LRPredictionSet : public PredictionSet {
public:
  typedef Simone::Ptr<const LRPredictionSet> PtrConst;
  typedef Simone::Ptr<LRPredictionSet> Ptr;

  static Ptr LRPredictionSetNew() { return new LRPredictionSet(); }

private:
  LRPredictionSet() {}

  /* disallowed operations */
  LRPredictionSet(const LRPredictionSet&);
  void operator=(const LRPredictionSet&);
};

} /* end of namespace Radon */

#endif
