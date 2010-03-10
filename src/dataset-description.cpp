#include "dataset-description.h"

namespace Radon {

DatasetDescription::DatasetDescription(uint32_t _data_vectors, uint32_t _vars,
                                       uint32_t _var_values) :  
  data_set_(boost::extents[_data_vectors][_vars][_var_values]) {}

} /* end of namespace Radon */

DatasetDescription(const string &filename) {
  
}