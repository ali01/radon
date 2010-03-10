#ifndef OUTCOME_H_PCDL3UT4
#define OUTCOME_H_PCDL3UT4

#include <simone/ptr_interface.h>

namespace Radon {

class Outcome : public Simone::PtrInterface<Outcome> {
public:
  typedef Simone::Ptr<const Outcome> PtrConst;

  static PtrConst OutcomeNew(uint32_t _value) {
    return new Outcome(_value);
  }

  uint32_t value() const { return value_; }
private:
  Outcome(uint32_t _value) : value_(_value) {}

  /* data members */
  uint32_t value_;

  /* disallowed operations */
  Outcome(const Outcome&);
  void operator=(const Outcome&);
};

} /* end of namespace Radon */

#endif
