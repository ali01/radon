#ifndef LR_CLASSIFIER_H_FGVOYBBB
#define LR_CLASSIFIER_H_FGVOYBBB

#include <simone/vector.h>

#include "classifier.h"
#include "dataset-description.h"
#include "data-instance.h"
#include "output-prediction-set.h"

#include "beta-set.h"

namespace Radon {

class LRClassifier : public Classifier {
public:
  typedef Simone::Ptr<const LRClassifier> PtrConst;
  typedef Simone::Ptr<LRClassifier> Ptr;

  /* default number of passes over the data that the algorithm will make in its
     training phase while learning the parameters of its predictive model */
  static const uint32_t kEpochsDefault = 1e4;

  /* default size of jump step used in each iteration as the algorithm converges
     on the global maximum of the log-likelihood function of the data */
  static const double kLearningRateDefault = 1.0e-4;

  /* default probability threshold used to decide whether to predict a value of
     1 or 0 for the output variable */
  static const double kThresholdDefault = 0.5;

  /* LRClassifier currently assumes domain and ranges of {0:1} */
  static const double kRangeSize = 2;
  static const double kDomainSize = 2;

  static Ptr LRClassifierNew(DatasetDescription::PtrConst training_data,
                             uint32_t _epochs=kEpochsDefault,
                             double _learning_rate=kLearningRateDefault,
                             double _threshold=kThresholdDefault) {
    return new LRClassifier(training_data, _epochs, _learning_rate, _threshold);
  }

private:

  LRClassifier(DatasetDescription::PtrConst training_data, uint32_t _epochs,
               double _learning_rate, double _threshold);

  /* member functions */

  /* overrides pure virtual function in base class;
     computes an output prediction for the given INPUT_VECTOR in DATASET */
  Observation prediction(DataInstance::PtrConst _instance) const;

  /* returns the probability P(Y=y, X) where y is the specified observation and
     X is the specified data instance (input vector) */
  double condProb(const Observation& _out_y,
                  DataInstance::PtrConst _instance) const;

  /* data members */

  /* set of beta parameters used to compute the value of the logistic function
     on any given data vector */
  BetaSet::Ptr beta_;

  /* probability threshold used to decide whether to predict a value of 1 or
     0 for the output variable */
  const double threshold_;

  /* disallowed operations */
  LRClassifier(const LRClassifier&);
  void operator=(const LRClassifier&);
};

} /* end of namespace Radon */

#endif
