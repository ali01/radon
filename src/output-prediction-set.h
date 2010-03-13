#ifndef PREDICTION_H_DN1M8644
#define PREDICTION_H_DN1M8644

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "output-prediction.h"

namespace Radon {

class OutputPredictionSet : public Simone::PtrInterface<OutputPredictionSet> {
public:
  typedef Simone::Ptr<const OutputPredictionSet> PtrConst;
  typedef Simone::Ptr<OutputPredictionSet> Ptr;

  static Ptr OutputPredictionSetNew() {
    return new OutputPredictionSet();
  }

  size_t size() const { return prediction_.size(); }
  void pushBack(OutputPrediction::PtrConst _prediction);

private:
  const static uint32_t kStatsIndexCorrect = 0;
  const static uint32_t kStatsIndexTested = 1;

  OutputPredictionSet() {}

  /* data members */
  Vector<OutputPrediction::PtrConst> prediction_;

  multi_array<uint32_t,2> stats_;


  /* disallowed operations */
  OutputPredictionSet(const OutputPredictionSet&);
  void operator=(const OutputPredictionSet&);
};

} /* end of namespace Radon */

#endif
