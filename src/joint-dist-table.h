#ifndef JOINT_DIST_TABLE_H_JJG1PMOA
#define JOINT_DIST_TABLE_H_JJG1PMOA

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>

#include "observation.h"

namespace Radon {

class JointDistTable : public Simone::PtrInterface<JointDistTable> {
public:
  typedef Simone::Ptr<const JointDistTable> Ptr;
  typedef Simone::Ptr<JointDistTable> PtrConst;

  static Ptr JointDistTableNew() { return new JointDistTable(); }

  Observation::PtrConst observation(uint32_t var, uint32_t out) const;

  uint32_t observationFreq(uint32_t var, uint32_t out) const;
  void observationFreqIs(uint32_t var, uint32_t out, uint32_t value);
  void observationFreqInc(uint32_t var, uint32_t out);
  void observationFreqDec(uint32_t var, uint32_t out);

private:
  JointDistTable();

  /* data members */
  multi_array<Observation::Ptr,2> dist_table_;

  /* disallowed operations */
  JointDistTable(const JointDistTable&);
  void operator=(const JointDistTable&);
};

} /* end of namespace Radon */

#endif
