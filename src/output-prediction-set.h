#ifndef PREDICTION_H_DN1M8644
#define PREDICTION_H_DN1M8644

#include <ostream>

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

  static Ptr OutputPredictionSetNew(uint32_t _range_size) {
    return new OutputPredictionSet(_range_size);
  }

  void pushBack(OutputPrediction::PtrConst _prediction);

  friend ostream& operator<<(ostream&, const OutputPredictionSet&);

private:
  OutputPredictionSet(uint32_t _range_size);

  uint32_t rangeSize() const { return tested_.size(); }

  uint32_t correctTotal() const;
  uint32_t testedTotal() const;
  double accuracy() const;

  /* data members */

  Vector<OutputPrediction::PtrConst> prediction_;

  /* prediction set statistics */
  Vector<uint32_t> correct_;
  Vector<uint32_t> tested_;

  /* disallowed operations */
  OutputPredictionSet(const OutputPredictionSet&);
  void operator=(const OutputPredictionSet&);
};

} /* end of namespace Radon */

#endif
