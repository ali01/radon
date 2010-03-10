#ifndef NAIVE_BAYES_H_KJPCTBNX
#define NAIVE_BAYES_H_KJPCTBNX

#include <simone/ptr_interface.h>

#include "classifier.h"

namespace Radon {

/* forward declarations */
class NBPredictionSet;

class NBClassifier : public Classifier {
public:
  typedef Simone::Ptr<const NBClassifier> PtrConst;
  typedef Simone::Ptr<NBClassifier> Ptr;

  enum EstMode { kML, kLaplace };

  static Ptr NBClassifierNew() { return new NBClassifier(); }

  PredictionSet::PtrConst predictionSet(EstMode _mode);

private:
  NBClassifier() {}

  /* override base class virtual function */
  PredictionSet::PtrConst predictionSet() { return predictionSet(kLaplace); }

  void train_algorithm(EstMode _mode);
  PredictionSet::PtrConst compute_prediction_set(EstMode _mode);

  /* disallowed operations */
  NBClassifier(const NBClassifier&);
  NBClassifier& operator=(const NBClassifier&);
};

} /* end of namespace Radon */

#endif
