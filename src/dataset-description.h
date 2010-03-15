#ifndef DATASET_DESCRIPTION_H_QZLQTVW1
#define DATASET_DESCRIPTION_H_QZLQTVW1

#include <stdint.h>
#include <string>
using std::string;

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>
#include <simone/vector.h>
#include <simone/deque.h>
using Simone::Vector;
using Simone::Deque;

#include "observation.h"
#include "data-instance.h"

namespace Radon {

class DatasetDescription : public Simone::PtrInterface<DatasetDescription> {
  friend class DatasetParser;
  friend class DataInstance;
public:
  typedef Simone::Ptr<const DatasetDescription> PtrConst;
  typedef Simone::Ptr<DatasetDescription> Ptr;

  static PtrConst DatasetDescriptionNew(uint32_t data_vectors, uint32_t vars) {
    return new DatasetDescription(data_vectors, vars);
  }

  DataInstance::PtrConst instance(uint32_t data_vector) const;

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
