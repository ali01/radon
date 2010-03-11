#include "joint-dist-table.h"

#include "globals.h"
#include "observation.h"

namespace Radon {

JointDistTable::JointDistTable() //:
  // prob_table_(boost::extents[kNumVarValues][kNumOutputValues])
{
  for (uint32_t var = 0; var < kNumVarValues; ++var) {
    for (uint32_t out = 0; out < kNumOutputValues; ++out) {
      // prob_table_[var][out] = Observation::ObservationNew();
    }
  }
}


} /* end of namespace Radon */
