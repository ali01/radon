#ifndef LR_CLASSIFIER_H_FGVOYBBB
#define LR_CLASSIFIER_H_FGVOYBBB

#include "classifier.h"
#include "output-prediction-set.h"

namespace Radon {

class LRClassifier : public Classifier {
public:
  typedef Simone::Ptr<const LRClassifier> PtrConst;
  typedef Simone::Ptr<LRClassifier> Ptr;

  static Ptr LRClassifierNew(DatasetDescription::PtrConst training_data) {
    return new LRClassifier(training_data);
  }

  OutputPredictionSet::PtrConst predictionSet() { return NULL; }

private:
  LRClassifier(DatasetDescription::PtrConst training_data);

  /* disallowed operations */
  LRClassifier(const LRClassifier&);
  void operator=(const LRClassifier&);
};

} /* end of namespace Radon */

#endif
