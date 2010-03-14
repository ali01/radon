#include "dataset-description.h"

#include "naive-bayes/frequency.h"

namespace Radon {

DatasetDescription::DatasetDescription(uint32_t _data_vectors, uint32_t _vars) :
  data_(boost::extents[_data_vectors][_vars]),
  data_vectors_(_data_vectors),
  vars_(_vars) {}

const Observation&
DatasetDescription::inputObservation(uint32_t data_vector, uint32_t var) const {
  return data_[data_vector][var];
}

const Observation&
DatasetDescription::outputObservation(uint32_t data_vector) const {
  return output_[data_vector];
}

DatasetDescription::Instance::PtrConst
DatasetDescription::instance(uint32_t data_vector) const {
  Instance::Ptr instance = Instance::VectorNew();

  /* populate instance with each var's observation */
  for (uint32_t var = 0; var < vars_; ++var)
    instance->pushBack(data_[data_vector][var]);

  return instance;
}

} /* end of namespace Radon */
