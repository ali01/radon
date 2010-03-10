#include "joint-dist-table.h"

#include "globals.h"
#include "observation.h"

namespace Radon {

JointDistTable::JointDistTable() :
  dist_table_(boost::extents[kNumVarValues][kNumOutputValues])
{
  for (uint32_t var = 0; var < kNumVarValues; ++var) {
    for (uint32_t out = 0; out < kNumOutputValues; ++out) {
      dist_table_[var][out] = Observation::ObservationNew();
    }
  }
}

Observation::PtrConst
JointDistTable::observation(uint32_t var, uint32_t out) const {
  return dist_table_[var][out];
}

void
JointDistTable::observationFreqIs(uint32_t var, uint32_t out, uint32_t value){
  dist_table_[var][out]->frequencyIs(value);
}

void
JointDistTable::observationFreqInc(uint32_t var, uint32_t out) {
  dist_table_[var][out]->frequencyInc();
}

void
JointDistTable::observationFreqDec(uint32_t var, uint32_t out) {
  dist_table_[var][out]->frequencyDec();
}

} /* end of namespace Radon */
