#include "dataset-description.h"

#include "observation.h"

namespace Radon {

DatasetDescription::DatasetDescription(uint32_t _data_vectors, uint32_t _vars,
                                       uint32_t _var_values)
  : observation_(boost::extents[_data_vectors][_vars][_var_values]) {
  for (uint32_t vec = 0; vec < _data_vectors; ++vec) {
    for (uint32_t var = 0; var < _vars; ++var) {
      for (uint32_t value = 0; value < _var_values; ++value) {
        observation_[vec][var][value] = Observation::ObservationNew();
      }
    }
  }
}

} /* end of namespace Radon */
