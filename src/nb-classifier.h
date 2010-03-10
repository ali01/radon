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

  PredictionSet::Ptr predictionSet() { return predictionSet(kLaplace); }
  PredictionSet::Ptr predictionSet(EstMode _mode);

private:
  NBClassifier() {}

  /* disallowed operations */
  NBClassifier(const NBClassifier&);
  NBClassifier& operator=(const NBClassifier&);
};

} /* end of namespace Radon */

#endif
