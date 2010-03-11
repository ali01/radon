#ifndef JOINT_DIST_TABLE_H_JJG1PMOA
#define JOINT_DIST_TABLE_H_JJG1PMOA

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>

#include "frequency.h"
#include "frequency-table.h"

namespace Radon {

class JointDistTable : public Simone::PtrInterface<JointDistTable> {
public:
  typedef Simone::Ptr<const JointDistTable> Ptr;
  typedef Simone::Ptr<JointDistTable> PtrConst;

  static Ptr JointDistTableNew(FrequencyTable::Ptr _freq_table) {
    return new JointDistTable(_freq_table);
  }

private:
  JointDistTable(FrequencyTable::Ptr _freq_table);

  /* data members */
  multi_array<Frequency::Ptr,2> prob_table_;

  /* disallowed operations */
  JointDistTable(const JointDistTable&);
  void operator=(const JointDistTable&);
};

} /* end of namespace Radon */

#endif
