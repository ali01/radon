#ifndef CLASSIFIER_H_47Z0UXCF
#define CLASSIFIER_H_47Z0UXCF

#include <simone/ptr_interface.h>

#include "dataset-description.h"
#include "prediction-set.h"

namespace Radon {

class Classifier : public Simone::PtrInterface<Classifier> {
public:
  typedef Simone::Ptr<const Classifier> PtrConst;
  typedef Simone::Ptr<Classifier> Ptr;

  void trainDatasetIs(DatasetDescription::PtrConst _data);
  void testDatasetIs(DatasetDescription::PtrConst _data);

  virtual PredictionSet::PtrConst predictionSet() = 0;
protected:
  Classifier() {}
  virtual ~Classifier() {}

  /* data members */
  DatasetDescription::PtrConst train_data_;
  DatasetDescription::PtrConst test_data_;

  PredictionSet::PtrConst prediction_set_;

private:
  /* disallowed operations */
  Classifier(const Classifier&);
  void operator=(const Classifier&);
};

} /* end of namespace Radon */

#endif
