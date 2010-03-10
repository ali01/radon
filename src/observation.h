#ifndef DATA_POINT_H_CERUAXL8
#define DATA_POINT_H_CERUAXL8

#include <simone/ptr_interface.h>

namespace Radon {

class Observation : public Simone::PtrInterface<Observation> {
public:
  typedef Simone::Ptr<const Observation> PtrConst;
  typedef Simone::Ptr<Observation> Ptr;

  static Ptr ObservationNew() { return new Observation(); }

  uint32_t frequency() const { return frequency_; }
  void frequencyIs(uint32_t _freq) { frequency_ = _freq; }
  void frequencyInc() { ++frequency_; }
  void frequencyDec() { --frequency_; }
private:
  Observation() : frequency_(0) {}

  /* data members */
  uint32_t frequency_;

  /* disallowed operations */
  Observation(const Observation&);
  Observation& operator=(const Observation&);
};

} /* end of namespace Radon */

#endif
