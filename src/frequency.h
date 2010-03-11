#ifndef DATA_POINT_H_CERUAXL8
#define DATA_POINT_H_CERUAXL8

#include <simone/ptr_interface.h>

namespace Radon {

class Frequency : public Simone::PtrInterface<Frequency> {
public:
  typedef Simone::Ptr<const Frequency> PtrConst;
  typedef Simone::Ptr<Frequency> Ptr;

  static Ptr FrequencyNew() { return new Frequency(); }

  uint32_t frequency() const { return frequency_; }
  void frequencyIs(uint32_t _freq) { frequency_ = _freq; }
  void frequencyInc() { ++frequency_; }
  void frequencyDec() { --frequency_; }
private:
  Frequency() : frequency_(0) {}

  /* data members */
  uint32_t frequency_;

  /* disallowed operations */
  Frequency(const Frequency&);
  Frequency& operator=(const Frequency&);
};

} /* end of namespace Radon */

#endif
