#ifndef NAIVE_BAYES_H_KJPCTBNX
#define NAIVE_BAYES_H_KJPCTBNX

#include <boost/multi_array.hpp>

#include <simone/ptr_interface.h>
#include <simone/vector.h>

#include "classifier.h"
#include "dataset-description.h"
#include "joint-dist-table.h"
#include "output-prediction.h"
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

  static Ptr NBClassifierNew(DatasetDescription::PtrConst training_data,
                             size_t _domain_size, size_t _range_size,
                             EstMode _mode) {
    return new NBClassifier(training_data, _domain_size, _range_size, _mode);
  }

  /* generates a set of predictions for TEST_DATA (see base class Classifier) */
  OutputPredictionSet::PtrConst predictionSet();

private:
  NBClassifier(DatasetDescription::PtrConst training_data,
               size_t _domain_size, size_t _range_size, EstMode _mode);

  /* private member functions */

  /* computes an output prediction for the given INPUT_VECTOR in DATASET */
  OutputPrediction::PtrConst prediction(DatasetDescription::PtrConst _dataset,
                                        uint32_t _input_vector) const;

  /* for a given INPUT_VECTOR in DATASET, returns the value of OUTPUT_VALUE
     that yields the maximum return value possible when passed into
     joint_prob_ln() */
  Observation joint_prob_arg_max(DatasetDescription::PtrConst _dataset,
                                 uint32_t _input_vector) const;

  /* returns the natural log of the probability P(X,Y) = P(X | Y) * P(Y) where
     X = INPUT_VECTOR and Y = OUTPUT_VALUE. Note that, because the Naive Bayes
     assumption, P(X | Y) is approximated by the product over all P(X_i | Y)
     or the sum of their logs. */
  ProbabilityLn joint_prob_ln(DatasetDescription::PtrConst _dataset,
                              uint32_t _input_vector,
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
