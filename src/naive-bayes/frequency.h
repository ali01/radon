#ifndef DATA_POINT_H_CERUAXL8
#define DATA_POINT_H_CERUAXL8

#include <stdint.h>

#include <simone/numeric.h>

namespace Radon {

class Frequency : public Simone::Numeric<Frequency,uint32_t> {
public:
  Frequency(uint32_t v=0) : Simone::Numeric<Frequency,uint32_t>(v) {}
};

} /* end of namespace Radon */

#endif
