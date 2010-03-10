#ifndef VARIABLE_H_PCDL3UT4
#define VARIABLE_H_PCDL3UT4

#include <simone/ptr_interface.h>

namespace Radon {

class Variable : public Simone::PtrInterface<Variable> {
public:
  typedef Simone::Ptr<const Variable> PtrConst;

  static PtrConst VariableNew(uint32_t _value) {
    return new Variable(_value);
  }

  uint32_t value() const { return value_; }
private:
  Variable(uint32_t _value) : value_(_value) {}

  /* data members */
  uint32_t value_;

  /* disallowed operations */
  Variable(const Variable&);
  void operator=(const Variable&);
};

} /* end of namespace Radon */

#endif
