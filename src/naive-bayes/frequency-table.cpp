#include "frequency-table.h"

#include "frequency.h"

namespace Radon {

FrequencyTable::FrequencyTable(size_t _domain_size, size_t _range_size,
                               Frequency _init_value) :
  freq_table_(boost::extents[_domain_size][_range_size]),
  domain_size_(_domain_size),
  range_size_(_range_size),
  count_(_init_value.value() * _domain_size * _range_size)
{
  for (size_t in_val = 0; in_val < domain_size_; ++in_val) {
    for (size_t out_val = 0; out_val < range_size_; ++out_val) {
      freq_table_[in_val][out_val] = _init_value;
    }
  }
}

Frequency
FrequencyTable::frequency(Observation in_val, Observation out_val) const {
  return freq_table_[in_val.value()][out_val.value()];
}

void
FrequencyTable::frequencyInc(Observation in_val, Observation out_val) {
  ++freq_table_[in_val.value()][out_val.value()];
  ++count_;
}

void
FrequencyTable::frequencyDec(Observation in_val, Observation out_val) {
  --freq_table_[in_val.value()][out_val.value()];
  --count_;
}

} /* end of namespace Radon */
