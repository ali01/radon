#ifndef FREQUENCY_TABLE_H_SWOZ24F2
#define FREQUENCY_TABLE_H_SWOZ24F2

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>

#include "frequency.h"

namespace Radon {

class FrequencyTable : public Simone::PtrInterface<FrequencyTable> {
public:
  typedef Simone::Ptr<const FrequencyTable> PtrConst;
  typedef Simone::Ptr<FrequencyTable> Ptr;

  static Ptr FrequencyTableNew(uint32_t var_vals, uint32_t output_vals) {
    return new FrequencyTable(var_vals, output_vals);
  }

  uint32_t frequency(uint32_t var_val, uint32_t out_val) const;
  void frequencyIs(uint32_t var_val, uint32_t out_val, uint32_t freq);
  void frequencyInc(uint32_t var_val, uint32_t out_val);
  void frequencyDec(uint32_t var_val, uint32_t out_val);
private:
  FrequencyTable(uint32_t var_vals, uint32_t output_vals);

  /* data members */
  multi_array<Frequency::Ptr,2> freq_table_;

  /* operations disallowed */
  FrequencyTable(const FrequencyTable&);
  void operator=(const FrequencyTable&);
};

} /* end of namespace Radon */

#endif
