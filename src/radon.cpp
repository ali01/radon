#include <string>
using std::string;

#include <simone/utility.h>

#include "globals.h"

#include "dataset-parser.h"
#include "dataset-description.h"
using Radon::DatasetParser;
using Radon::DatasetDescription;

int main() {
  DatasetDescription::Ptr train_dataset, test_dataset;
  DatasetParser::Ptr data_parser = DatasetParser::DatasetParserNew();

  string filepath_prefix;
  filepath_prefix += Radon::kDatasetPath;
  filepath_prefix += "/";
  filepath_prefix += Radon::kDataset;

  string filepath_suffix;
  filepath_suffix += Radon::kExtension;

  train_dataset = data_parser->datasetDescription(filepath_prefix +
                                                  Radon::kTrainFlag +
                                                  filepath_suffix);

  test_dataset = data_parser->datasetDescription(filepath_prefix +
                                                 Radon::kTestFlag +
                                                 filepath_suffix);
}
