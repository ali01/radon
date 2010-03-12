#include "joint-dist-table.h"

#include "globals.h"
#include "frequency.h"

namespace Radon {

JointDistTable::JointDistTable(FrequencyTable::Ptr _freq_table) :
  prob_table_(boost::extents[_freq_table->domainSize()]
                            [_freq_table->rangeSize()]),
  domain_size_(_freq_table->domainSize()),
  range_size_(_freq_table->rangeSize())
{
  uint32_t freq;
  double freq_double;
  for (uint32_t in_val = 0; in_val < _freq_table->domainSize(); ++in_val) {
    for (uint32_t out_val = 0; out_val < _freq_table->rangeSize(); ++out_val) {
      freq = _freq_table->frequency(in_val, out_val);
      freq_double = static_cast<double>(freq);

      /* probability for a single input -> output
         mapping is given by frequency/total_count */
      prob_table_[in_val][out_val] = freq_double / _freq_table->count();
    }
  }
}

Probability
JointDistTable::inputMarginal(uint32_t in_idx) {
  Probability in_marginal(0.0);
  for (uint32_t out_idx = 0; out_idx < range_size_; ++out_idx)
    in_marginal += prob_table_[in_idx][out_idx];
  return in_marginal;
}

Probability
JointDistTable::outputMarginal(uint32_t out_idx) {
  Probability out_marginal(0.0);
  for (uint32_t in_idx = 0; in_idx < domain_size_; ++in_idx)
    out_marginal += prob_table_[in_idx][out_idx];
  return out_marginal;
}

} /* end of namespace Radon */
