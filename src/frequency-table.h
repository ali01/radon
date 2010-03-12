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

  static Ptr FrequencyTableNew(uint32_t domain_size, uint32_t range_size) {
    return new FrequencyTable(domain_size, range_size);
  }

  void frequencyInc(uint32_t in_val, uint32_t out_val);
  void frequencyDec(uint32_t in_val, uint32_t out_val);

  uint32_t frequency(uint32_t in_val, uint32_t out_val) const;
  uint32_t domainSize() const { return domain_size_; }
  uint32_t rangeSize() const { return range_size_; }
  uint32_t count() const { return count_; }

private:
  FrequencyTable(uint32_t domain_size, uint32_t range_size);

  /* data members */
  multi_array<Frequency,2> freq_table_;

  uint32_t domain_size_;
  uint32_t range_size_;
  uint32_t count_;

  /* operations disallowed */
  FrequencyTable(const FrequencyTable&);
  void operator=(const FrequencyTable&);
};

} /* end of namespace Radon */

#endif
