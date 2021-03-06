#ifndef DATA_PARSER_H_JM6ROX9E
#define DATA_PARSER_H_JM6ROX9E

#include <string>
using std::string;

#include <simone/ptr_interface.h>

#include "dataset-description.h"

namespace Radon {

class DatasetParser : public Simone::PtrInterface<DatasetParser> {
public:
  typedef Simone::Ptr<const DatasetParser> PtrConst;

  static PtrConst DatasetParserNew() { return new DatasetParser(); }

  DatasetDescription::PtrConst
    datasetDescription(const string &_filepath) const;

private:
  DatasetParser() {}

  /* disallowed operations */
  DatasetParser(const DatasetParser&);
  void operator=(const DatasetParser&);
};

} /* end of namespace Radon */

#endif
