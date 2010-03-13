#include "output-prediction-set.h"

namespace Radon {

void
OutputPredictionSet::pushBack(OutputPrediction::PtrConst _prediction) {
  prediction_.pushBack(_prediction);
}

} /* end of namespace Radon */