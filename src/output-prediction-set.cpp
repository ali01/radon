#include "output-prediction-set.h"

namespace Radon {

OutputPredictionSet::OutputPredictionSet(uint32_t _range_size) {
  uint32_t stub = 0;
  for (uint32_t i = 0; i < _range_size; ++i) {
    correct_.pushBack(stub);
    tested_.pushBack(stub);
  }
}

void
OutputPredictionSet::pushBack(OutputPrediction::PtrConst _prediction) {
  Observation predicted = _prediction->predicted();
  Observation expected = _prediction->expected();

  /* increment test count for class */
  ++tested_[expected.value()];

  /* increment correct count for class */
  if (predicted == expected) {
    /* the value of expected identifies the true outcome
       hence, use as index in our prediction statistics model */
    ++correct_[expected.value()];
  }

  prediction_.pushBack(_prediction);
}

} /* end of namespace Radon */
