#include "joint-dist-table.h"

#include "globals.h"
#include "frequency.h"

namespace Radon {

JointDistTable::JointDistTable(FrequencyTable::Ptr _freq_table) :
  prob_table_(boost::extents[_freq_table->domainSize()]
                            [_freq_table->rangeSize()]),
  domain_size_(_freq_table->domainSize()),
  range_size_(_freq_table->rangeSize())
{
  Frequency freq;
  double freq_double;
  for (size_t in_val = 0; in_val < _freq_table->domainSize(); ++in_val) {
    for (size_t out_val = 0; out_val < _freq_table->rangeSize(); ++out_val) {
      freq = _freq_table->frequency(in_val, out_val);
      freq_double = static_cast<double>(freq.value());

      /* probability for a single input -> output
         mapping is given by frequency/total_count */
      prob_table_[in_val][out_val] = freq_double / _freq_table->count();
    }
  }
}

Probability
JointDistTable::inputConditional(Observation in_idx,
                                 Observation out_condition) const {
  /* input conditional probability is equal to P(X,Y) / P(Y) */
  Probability in_conditional = prob_table_[in_idx.value()][out_condition.value()];
  in_conditional /= outputMarginal(out_condition);
  return in_conditional;
}

Probability
JointDistTable::outputConditional(Observation out_idx,
                                  Observation in_condition) const {
  /* output conditional probability is equal to P(X,Y) / P(X) */
  Probability out_conditional = prob_table_[in_condition.value()][out_idx.value()];
  out_conditional /= inputMarginal(in_condition);
  return out_conditional;
}

Probability
JointDistTable::inputMarginal(Observation in_idx) const {
  Probability in_marginal(0.0);
  for (size_t out_idx = 0; out_idx < range_size_; ++out_idx)
    in_marginal += prob_table_[in_idx.value()][out_idx];
  return in_marginal;
}

Probability
JointDistTable::outputMarginal(Observation out_idx) const {
  Probability out_marginal(0.0);
  for (size_t in_idx = 0; in_idx < domain_size_; ++in_idx)
    out_marginal += prob_table_[in_idx][out_idx.value()];
  return out_marginal;
}

} /* end of namespace Radon */
