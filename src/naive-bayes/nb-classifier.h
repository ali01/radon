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
class NBOutputPredictionSet;

class NBClassifier : public Classifier {
public:
  typedef Simone::Ptr<const NBClassifier> PtrConst;
  typedef Simone::Ptr<NBClassifier> Ptr;

  enum EstMode { kML, kLaplace };

  /* LRClassifier currently assumes domain and ranges of {0:1} */
  static const double kRangeSize = 2;
  static const double kDomainSize = 2;

  static Ptr NBClassifierNew(DatasetDescription::PtrConst training_data,
                             EstMode _mode) {
    return new NBClassifier(training_data, _mode);
  }

private:
  NBClassifier(DatasetDescription::PtrConst training_data, EstMode _mode);

  /* private member functions */

  /* overrides pure virtual function in base class;
     computes an output prediction for the given input vector INSTANCE */
  Observation prediction(DataInstance::PtrConst _instance) const;

  /* for a given input vector INSTANCE, returns the value of OUTPUT_VALUE
     that yields the maximum return value possible when passed into
     joint_prob_ln() */
  Observation joint_prob_arg_max(DataInstance::PtrConst _instance) const;

  /* returns the natural log of the probability P(X,Y) = P(X | Y) * P(Y) where
     X = INSTANCE and Y = OUTPUT_VALUE. Note that, because the Naive Bayes
     assumption, P(X | Y) is approximated by the product over all P(X_i | Y)
     or the sum of their logs. */
  ProbabilityLn joint_prob_ln(DataInstance::PtrConst _instance,
                              Observation _output_value) const;

  /* data members */

  /* vector of each variable's joint probability distribution */
  Vector<JointDistTable::Ptr> joint_dist_;

  /* vector of each outcome's marginal probability */
  Vector<Probability> out_marginal_;

  /* disallowed operations */
  NBClassifier(const NBClassifier&);
  NBClassifier& operator=(const NBClassifier&);
};

} /* end of namespace Radon */

#endif
