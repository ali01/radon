#include "frequency-table.h"

#include "frequency.h"

namespace Radon {

FrequencyTable::FrequencyTable(uint32_t _domain_size, uint32_t _range_size) :
  freq_table_(boost::extents[_domain_size][_range_size]),
  domain_size_(_domain_size),
  range_size_(_range_size),
  count_(0)
{
  for (uint32_t in_val = 0; in_val < domain_size_; ++in_val) {
    for (uint32_t out_val = 0; out_val < range_size_; ++out_val) {
      freq_table_[in_val][out_val] = Frequency();
    }
  }
}

uint32_t
FrequencyTable::frequency(uint32_t in_val, uint32_t out_val) const {
  return freq_table_[in_val][out_val].frequency();
}

void
FrequencyTable::frequencyInc(uint32_t in_val, uint32_t out_val) {
  freq_table_[in_val][out_val].frequencyInc();
  ++count_;
}

void
FrequencyTable::frequencyDec(uint32_t in_val, uint32_t out_val) {
  freq_table_[in_val][out_val].frequencyDec();
  --count_;
}

} /* end of namespace Radon */
