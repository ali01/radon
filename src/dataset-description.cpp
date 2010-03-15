#include "dataset-description.h"

#include "naive-bayes/frequency.h"

namespace Radon {

DatasetDescription::DatasetDescription(uint32_t _data_vectors, uint32_t _vars) :
  data_(boost::extents[_data_vectors][_vars]),
  data_vectors_(_data_vectors),
  vars_(_vars) {}

DataInstance::PtrConst
DatasetDescription::instance(uint32_t data_vector) const {
  return DataInstance::DataInstanceNew(this, data_vector);
}

} /* end of namespace Radon */
