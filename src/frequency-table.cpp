#include "frequency-table.h"

#include "frequency.h"

namespace Radon {

FrequencyTable::FrequencyTable(uint32_t var_vals, uint32_t output_vals) :
  freq_table_(boost::extents[var_vals][output_vals])
{
  for (uint32_t var_val = 0; var_val < var_vals; ++var_val) {
    for (uint32_t out_val = 0; out_val < output_vals; ++out_val) {
      freq_table_[var_val][out_val] = Frequency::FrequencyNew();
    }
  }
}

uint32_t
FrequencyTable::frequency(uint32_t var_val, uint32_t out_val) const {
  return freq_table_[var_val][out_val]->frequency();
}

void
FrequencyTable::frequencyIs(uint32_t var_val, uint32_t out_val, uint32_t freq) {
  freq_table_[var_val][out_val]->frequencyIs(freq);
}

void
FrequencyTable::frequencyInc(uint32_t var_val, uint32_t out_val) {
  freq_table_[var_val][out_val]->frequencyInc();
}

void
FrequencyTable::frequencyDec(uint32_t var_val, uint32_t out_val) {
  freq_table_[var_val][out_val]->frequencyDec();
}

} /* end of namespace Radon */
