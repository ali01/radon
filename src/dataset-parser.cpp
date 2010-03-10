#include "dataset-parser.h"

#include <fstream>
using std::ifstream;

#include <simone/utility.h>

#include "variable.h"

namespace Radon {

DatasetDescription::PtrConst
DatasetParser::datasetDescription(const string &_filepath) const {
  ifstream data_stream(_filepath.c_str());
  uint32_t data_vectors, vars;
  DatasetDescription::PtrConst dataset_const;
  DatasetDescription::Ptr dataset;

  data_stream >> vars;
  data_stream >> data_vectors;

  /* const_cast friend dataset for initialization */
  dataset_const = DatasetDescription::DatasetDescriptionNew(data_vectors, vars);
  dataset = const_cast<DatasetDescription *>(dataset_const.ptr());

  uint32_t value;
  Variable::PtrConst output;

  for (uint32_t vec = 0; vec < data_vectors; ++vec) {
    /* parse inpupt vector data and populate dataset */
    for (uint32_t var = 0; var < vars; ++var) {
      data_stream >> value;
      dataset->data_[vec][var] = Variable::VariableNew(value);
    }

    /* ignore colon separator */
    data_stream.ignore(std::numeric_limits<std::streamsize>::max(), ':');

    /* parse expected output */
    data_stream >> value;
    output = Variable::VariableNew(value);
    dataset->output_.pushBack(output);

    /* ignore new line character */
    if (!data_stream.eof())
      data_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  /* TODO: throw exception */
  assert(!data_stream.fail());

  return dataset;
}

} /* end of namespace Radon */
