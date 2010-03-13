#include "output-prediction-set.h"

#include <iostream>
using std::cout;
using std::endl;

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

ostream&
operator<<(ostream &out, const OutputPredictionSet &ps) {
  for (uint32_t i = 0; i < ps.rangeSize(); ++i) {
    /* print class number (expected outcome) */
    cout << "Class " << i << ": ";

    /* print total number of times class i was tested */
    cout << "tested " << ps.tested_[i] << ", ";

    /* print the total number of times class i was correctly predicted */
    cout << "correctly classified " << ps.correct_[i] << "\n";
  }

  /* overall statistics */
  cout << "Overall: tested " << ps.testedTotal() << ", ";
  cout << "correctly classified " << ps.correctTotal() << "\n";

  /* accuracy */
  cout << "Accuracy = " << ps.accuracy() << "\n";
  return out;
}

/* private member functions */

uint32_t
OutputPredictionSet::correctTotal() const {
  uint32_t sum = 0;
  for (uint32_t i = 0; i < correct_.size(); ++i)
    sum += correct_[i];
  return sum;
}

uint32_t
OutputPredictionSet::testedTotal() const {
  uint32_t sum = 0;
  for (uint32_t i = 0; i < tested_.size(); ++i)
    sum += tested_[i];
  return sum;
}

double
OutputPredictionSet::accuracy() const {
  double correct = static_cast<double>(correctTotal());
  return correct / testedTotal();
}

} /* end of namespace Radon */
