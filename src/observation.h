#ifndef VARIABLE_H_PCDL3UT4
#define VARIABLE_H_PCDL3UT4

#include <stdint.h>
#include <simone/numeric.h>

namespace Radon {

class Observation : public Simone::Numeric<Observation,uint32_t> {
public:
  static const Observation kInvalid;
  Observation() : Simone::Numeric<Observation,uint32_t>(kInvalid) {}
  Observation(uint32_t v) : Simone::Numeric<Observation,uint32_t>(v) {}
};

} /* end of namespace Radon */

#endif
