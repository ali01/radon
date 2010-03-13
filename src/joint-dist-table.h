#ifndef JOINT_DIST_TABLE_H_JJG1PMOA
#define JOINT_DIST_TABLE_H_JJG1PMOA

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>

#include "frequency-table.h"
#include "observation.h"
#include "probability.h"

namespace Radon {

class JointDistTable : public Simone::PtrInterface<JointDistTable> {
public:
  typedef Simone::Ptr<const JointDistTable> Ptr;
  typedef Simone::Ptr<JointDistTable> PtrConst;

  static Ptr JointDistTableNew(FrequencyTable::Ptr _freq_table) {
    return new JointDistTable(_freq_table);
  }

  Probability inputConditional(Observation in_idx, Observation out_condition) const;
  Probability outputConditional(Observation out_idx, Observation in_condition) const;

  Probability inputMarginal(Observation in_idx) const;
  Probability outputMarginal(Observation out_idx) const;

private:
  JointDistTable(FrequencyTable::Ptr _freq_table);

  /* data members */
  multi_array<Probability,2> prob_table_;

  size_t domain_size_;
  size_t range_size_;

  /* disallowed operations */
  JointDistTable(const JointDistTable&);
  void operator=(const JointDistTable&);
};

} /* end of namespace Radon */

#endif
