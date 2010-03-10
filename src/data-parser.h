#ifndef DATA_PARSER_H_JM6ROX9E
#define DATA_PARSER_H_JM6ROX9E

#include <string>
using std::string;

#include <simone/ptr_interface.h>

namespace Radon {

class DatasetParser : public Simone::PtrInterface<DatasetParser> {
public:
  typedef Simone::Ptr<const DatasetParser> PtrConst;
  typedef Simone::Ptr<DatasetParser> Ptr;

  static Ptr DatasetParserNew(const string &filename) {
    return new DatasetParser(filename);
  }

  uint32_t dataVectorCount() const;
  uint32_t varCount() const;
  uint32_t varValueCount() const;

private:
  DatasetParser(const string &filename);

  /* disallowed operations */
  DatasetParser(const DatasetParser&);
  void operator=(const DatasetParser&);
};

} /* end of namespace Radon */

#endif
