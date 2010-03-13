#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <simone/utility.h>

#include "globals.h"

#include "dataset-parser.h"
#include "dataset-description.h"
#include "lr-classifier.h"
#include "nb-classifier.h"
#include "output-prediction-set.h"
using Radon::DatasetParser;
using Radon::DatasetDescription;
using Radon::LRClassifier;
using Radon::NBClassifier;
using Radon::OutputPredictionSet;

int main() {
  string filepath_prefix, filepath_suffix;
  DatasetDescription::PtrConst train_dataset, test_dataset;
  DatasetParser::PtrConst data_parser;
  NBClassifier::Ptr nb_mle_classifier;
  LRClassifier::Ptr lr_classifier;
  OutputPredictionSet::PtrConst nb_mle_prediction, nb_laplace_prediction;
  OutputPredictionSet::PtrConst lr_prediction;

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

  nb_mle_classifier = NBClassifier::NBClassifierNew(train_dataset);
  nb_mle_classifier->testDatasetIs(test_dataset);

  nb_mle_prediction = nb_mle_classifier->predictionSet();

  cout << nb_mle_classifier << endl;
}
