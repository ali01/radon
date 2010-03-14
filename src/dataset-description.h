#ifndef DATASET_DESCRIPTION_H_QZLQTVW1
#define DATASET_DESCRIPTION_H_QZLQTVW1

#include <stdint.h>
#include <string>
using std::string;

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>
#include <simone/vector.h>
using Simone::Vector;

#include "naive-bayes/frequency.h"
#include "observation.h"

namespace Radon {

class DatasetDescription : public Simone::PtrInterface<DatasetDescription> {
  friend class DatasetParser;
public:
  typedef Simone::Ptr<const DatasetDescription> PtrConst;
  typedef Simone::Ptr<DatasetDescription> Ptr;

  typedef Vector<Observation> Instance;

  static PtrConst DatasetDescriptionNew(uint32_t data_vectors, uint32_t vars) {
    return new DatasetDescription(data_vectors, vars);
  }

  const Observation& inputObservation(uint32_t data_vector, uint32_t var) const;
  const Observation& outputObservation(uint32_t data_vector) const;

  Instance::PtrConst instance(uint32_t data_vector) const;

  uint32_t vectorCount() const { return data_vectors_; }
  uint32_t varCount() const { return vars_; }

private:
  DatasetDescription(uint32_t data_vectors, uint32_t vars);

  /* data members */
  multi_array<Observation,2> data_;
  Vector<Observation> output_;

  uint32_t data_vectors_;
  uint32_t vars_;

  /* disallowed operations */
  DatasetDescription(const DatasetDescription&);
  DatasetDescription& operator=(const DatasetDescription&);
};

} /* end of namespace Radon */

#endif
