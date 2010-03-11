#include "joint-dist-table.h"

#include "globals.h"
#include "frequency.h"

namespace Radon {

JointDistTable::JointDistTable(FrequencyTable::Ptr _freq_table) :
  prob_table_(boost::extents[_freq_table->domainSize()]
                            [_freq_table->rangeSize()])
{
  for (uint32_t in_val = 0; in_val < _freq_table->domainSize(); ++in_val) {
    for (uint32_t out_val = 0; out_val < _freq_table->rangeSize(); ++out_val) {
      // prob_table_[in_val][out_val] = Frequency::FrequencyNew();
    }
  }
}


} /* end of namespace Radon */
