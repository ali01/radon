#ifndef PREDICTION_H_XPYR6044
#define PREDICTION_H_XPYR6044

#include <simone/ptr_interface.h>

#include "dataset-description.h"

namespace Radon {

class OutputPrediction : public Simone::PtrInterface<OutputPrediction> {
public:
  typedef Simone::Ptr<const OutputPrediction> PtrConst;
  typedef Simone::Ptr<OutputPrediction> Ptr;

  static Ptr OutputPredictionNew(DatasetDescription::PtrConst _dataset,
                                 uint32_t _input_vector,
                                 Observation _output_prediction) {
    return new OutputPrediction(_dataset, _input_vector, _output_prediction);
  }

private:
  OutputPrediction(DatasetDescription::PtrConst _dataset,
                   uint32_t _input_vector, Observation _output_prediction);

  DatasetDescription::PtrConst dataset_;
  uint32_t input_vector_;
  Observation output_prediction_;


  /* disallowed operations */
  OutputPrediction(const OutputPrediction&);
  void operator=(const OutputPrediction&);
};

} /* end of namespace Radon */

#endif
