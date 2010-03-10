#ifndef LR_CLASSIFIER_H_FGVOYBBB
#define LR_CLASSIFIER_H_FGVOYBBB

#include "classifier.h"
#include "lr-prediction-set.h"

namespace Radon {

class LRClassifier : public Classifier {
public:
  typedef Simone::Ptr<const LRClassifier> PtrConst;
  typedef Simone::Ptr<LRClassifier> Ptr;

  static Ptr LRClassifierNew() { return new LRClassifier(); }

  PredictionSet::Ptr predictionSet() { return NULL; }

private:
  LRClassifier() {}

  LRPredictionSet::Ptr prediction_set_;

  /* disallowed operations */
  LRClassifier(const LRClassifier&);
  void operator=(const LRClassifier&);
};

} /* end of namespace Radon */

#endif
