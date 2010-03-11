#include "frequency-table.h"

namespace Radon {

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