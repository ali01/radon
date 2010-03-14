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

  /* value defines the default number of passes over the data that the algorithm
     will make in its training phase while learning the parameters of its
     predictive model */
  static const uint32_t kEpochsDefault = 1e4;
  static const double kLearningRateDefault = 1.0e-4;

  static Ptr LRClassifierNew(DatasetDescription::PtrConst training_data,
                             size_t _domain_size, size_t _range_size,
                             uint32_t _epochs=kEpochsDefault,
                             double _learning_rate=kLearningRateDefault) {
    return new LRClassifier(training_data, _domain_size, _range_size,
                            _epochs, _learning_rate);
  }

  OutputPredictionSet::PtrConst predictionSet();

  /* static public functions */
  static DataInstance::PtrConst
  data_instance(DatasetDescription::PtrConst _dataset, uint32_t idx);

private:
  LRClassifier(DatasetDescription::PtrConst training_data,
               size_t _domain_size, size_t _range_size,
               uint32_t _epochs, double _learning_rate);

  /* member functions */
  // OutputPrediction::PtrConst prediction()

  /* data members */
  BetaSet::Ptr beta_;

  /* disallowed operations */
  LRClassifier(const LRClassifier&);
  void operator=(const LRClassifier&);
};

} /* end of namespace Radon */

#endif
