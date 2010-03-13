#ifndef FREQUENCY_TABLE_H_SWOZ24F2
#define FREQUENCY_TABLE_H_SWOZ24F2

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>

#include "frequency.h"
#include "observation.h"

namespace Radon {

class FrequencyTable : public Simone::PtrInterface<FrequencyTable> {
public:
  typedef Simone::Ptr<const FrequencyTable> PtrConst;
  typedef Simone::Ptr<FrequencyTable> Ptr;

  static Ptr FrequencyTableNew(size_t domain_size, size_t range_size) {
    return new FrequencyTable(domain_size, range_size);
  }

  /* increment or decrement observation specified by IN_VAL and OUT_VAL */
  void frequencyInc(Observation in_val, Observation out_val);
  void frequencyDec(Observation in_val, Observation out_val);

  Frequency frequency(Observation in_val, Observation out_val) const;
  size_t domainSize() const { return domain_size_; }
  size_t rangeSize() const { return range_size_; }
  size_t count() const { return count_; }

private:
  FrequencyTable(size_t domain_size, size_t range_size);

  /* data members */
  multi_array<Frequency,2> freq_table_;

  size_t domain_size_;
  size_t range_size_;
  size_t count_;

  /* operations disallowed */
  FrequencyTable(const FrequencyTable&);
  void operator=(const FrequencyTable&);
};

} /* end of namespace Radon */

#endif
