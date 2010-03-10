#ifndef NAIVE_BAYES_H_KJPCTBNX
#define NAIVE_BAYES_H_KJPCTBNX

#include <boost/multi_array.hpp>

#include <simone/ptr_interface.h>
#include <simone/vector.h>

#include "classifier.h"
#include "dataset-description.h"

namespace Radon {

/* forward declarations */
class NBPredictionSet;

class NBClassifier : public Classifier {
public:
  typedef Simone::Ptr<const NBClassifier> PtrConst;
  typedef Simone::Ptr<NBClassifier> Ptr;

  enum EstMode { kML, kLaplace };

  static Ptr NBClassifierNew(DatasetDescription::PtrConst training_data) {
    return new NBClassifier(training_data);
  }

  PredictionSet::PtrConst predictionSet(EstMode _mode);

private:
  NBClassifier(DatasetDescription::PtrConst training_data);

  /* override base class virtual function */
  PredictionSet::PtrConst predictionSet() { return predictionSet(kLaplace); }

  /* private member functions */
  PredictionSet::PtrConst compute_prediction_set(EstMode _mode);

  /* data members */
  Vector<multi_array<Observation::Ptr,2> > data_map_;

  /* disallowed operations */
  NBClassifier(const NBClassifier&);
  NBClassifier& operator=(const NBClassifier&);
};

} /* end of namespace Radon */

#endif
