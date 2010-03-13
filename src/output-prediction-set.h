#ifndef PREDICTION_H_DN1M8644
#define PREDICTION_H_DN1M8644

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "output-prediction.h"

namespace Radon {

class OutputPredictionSet : public Simone::PtrInterface<OutputPredictionSet> {
public:
  typedef Simone::Ptr<const OutputPredictionSet> PtrConst;
  typedef Simone::Ptr<OutputPredictionSet> Ptr;

  static Ptr OutputPredictionSetNew() { return new OutputPredictionSet(); }

  void pushBack(OutputPrediction::PtrConst _prediction);

protected:
  OutputPredictionSet() {}

  /* data members */
  Vector<OutputPrediction::PtrConst> prediction_;

  size_t size() const { return prediction_.size(); }

private:
  /* disallowed operations */
  OutputPredictionSet(const OutputPredictionSet&);
  void operator=(const OutputPredictionSet&);
};

} /* end of namespace Radon */

#endif
