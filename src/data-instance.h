#ifndef DATA_INSTANCE_H_LZCKA10O
#define DATA_INSTANCE_H_LZCKA10O

#include <simone/ptr_interface.h>

#include "observation.h"

namespace Radon {

/* forward declarations */
class DatasetDescription;

class DataInstance : public Simone::PtrInterface<DataInstance> {
public:
  typedef Simone::Ptr<const DataInstance> PtrConst;

  static PtrConst
  DataInstanceNew(Simone::Ptr<const DatasetDescription> _dataset,
                  uint32_t _vector_idx) {
    return new DataInstance(_dataset, _vector_idx);
  }

  /* returns the value of input vector at index COMPONENT_IDX */
  const Observation& inputObservation(uint32_t component_idx) const;

  /* returns the expected (correct) output value for this input vector */
  const Observation& outputObservation() const;

  uint32_t varCount() const;

private:
  DataInstance(Simone::Ptr<const DatasetDescription> _dataset,
               uint32_t _vector_idx);

  /* data members */
  Simone::Ptr<const DatasetDescription> dataset_;
  const uint32_t vector_idx_;

  /* disallowed operations */
  DataInstance(const DataInstance&);
  void operator=(const DataInstance&);
};

} /* end of namespace Radon */

#endif
