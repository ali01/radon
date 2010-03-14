#ifndef LR_CLASSIFIER_H_FGVOYBBB
#define LR_CLASSIFIER_H_FGVOYBBB

#include "classifier.h"
#include "output-prediction-set.h"

namespace Radon {

class LRClassifier : public Classifier {
public:
  typedef Simone::Ptr<const LRClassifier> PtrConst;
  typedef Simone::Ptr<LRClassifier> Ptr;

  static Ptr LRClassifierNew(DatasetDescription::PtrConst training_data,
                             size_t _domain_size, size_t _range_size) {
    return new LRClassifier(training_data, _domain_size, _range_size);
  }

  OutputPredictionSet::PtrConst predictionSet() { return NULL; }

private:
  LRClassifier(DatasetDescription::PtrConst training_data,
               size_t _domain_size, size_t _range_size);

  /* data members */


  /* disallowed operations */
  LRClassifier(const LRClassifier&);
  void operator=(const LRClassifier&);
};

} /* end of namespace Radon */

#endif
