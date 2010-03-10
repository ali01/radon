#ifndef DATASET_DESCRIPTION_H_QZLQTVW1
#define DATASET_DESCRIPTION_H_QZLQTVW1

#include <stdint.h>
#include <string>
using std::string;

#include <boost/multi_array.hpp>
using boost::multi_array;

#include <simone/ptr_interface.h>

#include "data-point.h"

namespace Radon {

class DatasetDescription : public Simone::PtrInterface<DatasetDescription> {
public:
  typedef Simone::Ptr<const DatasetDescription> PtrConst;
  typedef Simone::Ptr<DatasetDescription> Ptr;

  static Ptr DatasetDescriptionNew(const string &filename) {
    return new DatasetDescription(filename);
  }

private:
  DatasetDescription(const string &filename);

  /* data members */
  multi_array<DataPoint::Ptr,3> data_set_;

  /* disallowed operations */
  DatasetDescription(const DatasetDescription&);
  DatasetDescription& operator=(const DatasetDescription&);
};

} /* end of namespace Radon */

#endif
