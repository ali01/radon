#ifndef DATA_POINT_H_CERUAXL8
#define DATA_POINT_H_CERUAXL8

#include <simone/numeric.h>

namespace Radon {

class Frequency : public Simone::Numeric<Frequency,uint32_t> {
public:
  Frequency(uint32_t v=0) : frequency_(v) {}
  uint32_t frequency() const { return frequency_; }
  void frequencyIs(uint32_t _freq) { frequency_ = _freq; }
  void frequencyInc() { ++frequency_; }
  void frequencyDec() { --frequency_; }

private:
  /* data members */
  uint32_t frequency_;
};

} /* end of namespace Radon */

#endif
