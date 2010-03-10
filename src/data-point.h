#ifndef DATA_POINT_H_CERUAXL8
#define DATA_POINT_H_CERUAXL8

#include <simone/ptr_interface.h>

namespace Radon {

class DataPoint : public Simone::PtrInterface<DataPoint> {
public:
  typedef Simone::Ptr<const DataPoint> PtrConst;
  typedef Simone::Ptr<DataPoint> Ptr;
  
  static Ptr DataPointNew() { return new DataPoint(); }
private:
  DataPoint() {}
  
  /* disallowed operations */
  DataPoint(const DataPoint&);
  DataPoint& operator=(const DataPoint&);
};

} /* end of namespace Radon */

#endif
