#ifndef LR_CLASSIFIER_H_FGVOYBBB
#define LR_CLASSIFIER_H_FGVOYBBB

#include <simone/vector.h>

#include "classifier.h"
#include "dataset-description.h"
#include "output-prediction.h"
#include "output-prediction-set.h"

#include "beta-set.h"

namespace Radon {

class LRClassifier : public Classifier {
  /* private typedef */
  typedef DatasetDescription::Instance DataInstance;
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

  static Ptr LRClassifierNew(DatasetDescription::PtrConst training_data,
                             size_t _domain_size, size_t _range_size,
                             uint32_t _epochs=kEpochsDefault,
                             double _learning_rate=kLearningRateDefault,
                             double _threshold=kThresholdDefault) {
    return new LRClassifier(training_data, _domain_size, _range_size,
                            _epochs, _learning_rate, _threshold);
  }

  OutputPredictionSet::PtrConst predictionSet();

  /* static public functions */
  static DataInstance::PtrConst
  data_instance(DatasetDescription::PtrConst _dataset, uint32_t idx);

private:
  LRClassifier(DatasetDescription::PtrConst training_data,
               size_t _domain_size, size_t _range_size, uint32_t _epochs,
               double _learning_rate, double _threshold);

  /* member functions */
  OutputPrediction::PtrConst prediction(DataInstance::PtrConst _instance);

  /* returns the probability P(Y=y, X) where y is the specified observation and
     X is the specified data instance (input vector) */
  double condProb(const Observation& _out_y, DataInstance::PtrConst _instance);

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
