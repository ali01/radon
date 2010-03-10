#include <string>
using std::string;

#include <simone/utility.h>

#include "globals.h"

#include "dataset-parser.h"
#include "dataset-description.h"
#include "lr-classifier.h"
#include "nb-classifier.h"
#include "prediction.h"
using Radon::DatasetParser;
using Radon::DatasetDescription;
using Radon::LRClassifier;
using Radon::NBClassifier;
using Radon::Prediction;

int main() {
  string filepath_prefix, filepath_suffix;
  DatasetDescription::Ptr train_dataset, test_dataset;
  DatasetParser::Ptr data_parser;
  NBClassifier::Ptr nb_classifier;
  LRClassifier::Ptr lr_classifier;
  Prediction::Ptr nb_mle_prediction, nb_laplace_prediction, lr_prediction;

  filepath_prefix =  Radon::kDatasetPath;
  filepath_prefix += "/";
  filepath_prefix += Radon::kDataset;

  filepath_suffix = Radon::kExtension;

  data_parser = DatasetParser::DatasetParserNew();
  train_dataset = data_parser->datasetDescription(filepath_prefix +
                                                  Radon::kTrainFlag +
                                                  filepath_suffix);

  test_dataset = data_parser->datasetDescription(filepath_prefix +
                                                 Radon::kTestFlag +
                                                 filepath_suffix);

  nb_classifier = NBClassifier::NBClassifierNew();
  nb_classifier->trainDatasetIs(train_dataset);
  nb_classifier->testDatasetIs(test_dataset);

  nb_mle_prediction = nb_classifier->prediction(NBClassifier::kML);
  nb_laplace_prediction = nb_classifier->prediction(NBClassifier::kLaplace);

  lr_classifier = LRClassifier::LRClassifierNew();
  lr_classifier->trainDatasetIs(train_dataset);
  lr_classifier->testDatasetIs(test_dataset);

  lr_prediction = lr_classifier->prediction();
}
