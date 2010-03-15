#include "data-instance.h"

#include "dataset-description.h"
#include "zero-data-instance.h"

namespace Radon {

DataInstance::DataInstance(DatasetDescription::PtrConst _dataset,
                           uint32_t _vector_idx) :
  dataset_(_dataset), vector_idx_(_vector_idx) {}

const Observation&
DataInstance::inputObservation(uint32_t component_idx) const {
  /* with friend access to dataset, return value of component idx inside of
     the dataset description's data_ multi_array */
  return dataset_->data_[vector_idx_][component_idx];
}

const Observation&
DataInstance::outputObservation() const {
  /* with friend access to dataset, return the output observation inside of
     the dataset description's output_ vector */
  return dataset_->output_[vector_idx_];
}

uint32_t
DataInstance::varCount() const {
  return dataset_->varCount();
}

} /* end of namespace Radon */