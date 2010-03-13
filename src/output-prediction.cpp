#include "output-prediction.h"

namespace Radon {

OutputPrediction::OutputPrediction(DatasetDescription::PtrConst _dataset,
                                   uint32_t _input_vector,
                                   Observation _output_prediction) :
  dataset_(_dataset),
  input_vector_(_input_vector),
  output_prediction_(_output_prediction) {}

} /* end of namespace Radon */
