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

#include "observation.h"
#include "outcome.h"

namespace Radon {

class DatasetDescription : public Simone::PtrInterface<DatasetDescription> {
  friend class DatasetParser;
public:
  typedef Simone::Ptr<const DatasetDescription> PtrConst;
  typedef Simone::Ptr<DatasetDescription> Ptr;

  static PtrConst DatasetDescriptionNew(uint32_t _data_vectors, uint32_t _vars,
                                        uint32_t _var_values=2) {
    return new DatasetDescription(_data_vectors, _var_values, _var_values);
  }

private:
  DatasetDescription(uint32_t _data_vectors, uint32_t _vars,
                     uint32_t _var_values);

  /* data members */
  multi_array<Observation::Ptr,3> observation_;
  Vector<Outcome::PtrConst> outcome_;

  /* disallowed operations */
  DatasetDescription(const DatasetDescription&);
  DatasetDescription& operator=(const DatasetDescription&);
};

} /* end of namespace Radon */

#endif
