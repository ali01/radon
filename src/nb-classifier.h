#ifndef NAIVE_BAYES_H_KJPCTBNX
#define NAIVE_BAYES_H_KJPCTBNX

#include <boost/multi_array.hpp>

#include <simone/ptr_interface.h>
#include <simone/vector.h>

#include "classifier.h"
#include "dataset-description.h"
#include "joint-dist-table.h"
#include "probability.h"
#include "probability-ln.h"

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
  PredictionSet::PtrConst prediction_set(EstMode _mode);
  ProbabilityLn input_conditional_ln_product(uint32_t var_idx, uint32_t in_val,
                                             uint32_t out_condition);

  /* data members */
  /* vector of each variable's joint probability distribution */
  Vector<JointDistTable::Ptr> joint_dist_;

  /* vector of each outcome's marginal probability */
  Vector<Probability> out_marginal_;

  uint32_t domain_size_;
  uint32_t range_size_;

  /* disallowed operations */
  NBClassifier(const NBClassifier&);
  NBClassifier& operator=(const NBClassifier&);
};

} /* end of namespace Radon */

#endif
