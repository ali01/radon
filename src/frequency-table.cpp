#include "frequency-table.h"

#include "frequency.h"

namespace Radon {

FrequencyTable::FrequencyTable(uint32_t vars, uint32_t vals) :
  freq_table_(boost::extents[vars][vals])
{
  for (uint32_t var = 0; var < vars; ++var) {
    for (uint32_t val = 0; val < vals; ++val) {
      freq_table_[var][val] = Frequency::FrequencyNew();
    }
  }
}

uint32_t
FrequencyTable::frequency(uint32_t var, uint32_t out) const {
  return freq_table_[var][out]->frequency();
}

void
FrequencyTable::frequencyIs(uint32_t var, uint32_t out, uint32_t value){
  freq_table_[var][out]->frequencyIs(value);
}

void
FrequencyTable::frequencyInc(uint32_t var, uint32_t out) {
  freq_table_[var][out]->frequencyInc();
}

void
FrequencyTable::frequencyDec(uint32_t var, uint32_t out) {
  freq_table_[var][out]->frequencyDec();
}

} /* end of namespace Radon */