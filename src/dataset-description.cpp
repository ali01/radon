#include "dataset-description.h"

#include "observation.h"

namespace Radon {

DatasetDescription::DatasetDescription(uint32_t _data_vectors, uint32_t _vars) :
  data_(boost::extents[_data_vectors][_vars]),
  data_vectors_(_data_vectors),
  vars_(_vars) {}

} /* end of namespace Radon */
