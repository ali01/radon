#ifndef CLASSIFIER_H_47Z0UXCF
#define CLASSIFIER_H_47Z0UXCF

#include <simone/ptr_interface.h>

#include "dataset-description.h"
#include "output-prediction-set.h"

namespace Radon {

class Classifier : public Simone::PtrInterface<Classifier> {
public:
  typedef Simone::Ptr<const Classifier> PtrConst;
  typedef Simone::Ptr<Classifier> Ptr;

  void testDatasetIs(DatasetDescription::PtrConst _data);

  virtual OutputPredictionSet::PtrConst predictionSet() = 0;

protected:
  Classifier(DatasetDescription::PtrConst _training_data,
             size_t _domain_size, size_t _range_size);
  virtual ~Classifier() {}

  /* data members */
  DatasetDescription::PtrConst training_data_;
  DatasetDescription::PtrConst test_data_;
  OutputPredictionSet::Ptr prediction_set_;

  size_t domain_size_;
  size_t range_size_;

private:
  /* disallowed operations */
  Classifier(const Classifier&);
  void operator=(const Classifier&);
};

} /* end of namespace Radon */

#endif
