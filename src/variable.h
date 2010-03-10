#ifndef VARIABLE_H_PCDL3UT4
#define VARIABLE_H_PCDL3UT4

#include <simone/ptr_interface.h>
#include <simone/numeric.h>

namespace Radon {

class Variable : public Simone::Numeric<Variable,uint32_t> {
public:
  static const Variable kInvalid;
  Variable() : Simone::Numeric<Variable,uint32_t>(kInvalid) {}
  Variable(uint32_t v) : Simone::Numeric<Variable,uint32_t>(v) {}
};

} /* end of namespace Radon */

#endif
