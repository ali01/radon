#ifndef NAIVE_BAYES_H_KJPCTBNX
#define NAIVE_BAYES_H_KJPCTBNX

#include <simone/ptr_interface.h>

#include "dataset-description.h"
#include "prediction.h"

namespace Radon {

class NaiveBayesClassifier : public Simone::PtrInterface<NaiveBayesClassifier> {
public:
  typedef Simone::Ptr<const NaiveBayesClassifier> PtrConst;
  typedef Simone::Ptr<NaiveBayesClassifier> Ptr;

  enum EstimationMode { kMLEstimation, kLaplaceEstimation };

  static Ptr NaiveBayesClassifierNew(DatasetDescription::Ptr _train_data,
                                     DatasetDescription::Ptr _test_data) {
    return new NaiveBayesClassifier(_train_data, _test_data);
  }

  Prediction::Ptr prediction(EstimationMode _mode);

private:
  NaiveBayesClassifier(DatasetDescription::Ptr _train_data,
                       DatasetDescription::Ptr _test_data);

  /* data members */
  DatasetDescription::Ptr train_data_;
  DatasetDescription::Ptr test_data_;

  /* disallowed operations */
  NaiveBayesClassifier(const NaiveBayesClassifier&);
  NaiveBayesClassifier& operator=(const NaiveBayesClassifier&);
};

} /* end of namespace Radon */

#endif
