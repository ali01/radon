#include <string>
using std::string;

#include <iostream>
using std::cout;

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
  /* file path string declarations */
  string filepath_prefix, filepath_suffix;

  /* dataset declarations */
  DatasetDescription::PtrConst train_dataset, test_dataset;

  /* parse declaration */
  DatasetParser::PtrConst data_parser;

  /* classifier declarations */
  NBClassifier::Ptr nb_mle, nb_lp;
  LRClassifier::Ptr lr_classifier;

  /* prediction declarations for Naive Bayes */
  OutputPredictionSet::PtrConst nb_mle_pd_set;
  OutputPredictionSet::PtrConst nb_lp_pd_set;

  /* prediction declaration for Logistic Regression */
  OutputPredictionSet::PtrConst lr_pd_set;

  /* building dataset file path */
  filepath_prefix =  Radon::kDatasetPath;
  filepath_prefix += "/";
  filepath_prefix += Radon::kDataset;

  filepath_suffix = Radon::kExtension;

  /* parsing and initializing datasets */
  data_parser = DatasetParser::DatasetParserNew();
  train_dataset = data_parser->datasetDescription(filepath_prefix +
                                                  Radon::kTrainFlag +
                                                  filepath_suffix);

  test_dataset = data_parser->datasetDescription(filepath_prefix +
                                                 Radon::kTestFlag +
                                                 filepath_suffix);

  /* initializing Naive Bayes classifier using maximum likelihood estimation */
  nb_mle = NBClassifier::NBClassifierNew(train_dataset, NBClassifier::kML);
  nb_mle->testDatasetIs(test_dataset);

  /* initializing Naive Bayes classifier using laplace estimation */
  nb_lp = NBClassifier::NBClassifierNew(train_dataset, NBClassifier::kLaplace);
  nb_lp->testDatasetIs(test_dataset);

  /* computing predictions for both MLE and Laplace */
  nb_mle_pd_set = nb_mle->predictionSet();
  nb_lp_pd_set = nb_lp->predictionSet();

  cout << "Prediction Results ~ Naive Bayes using MLE\n";
  cout << *nb_mle_pd_set << "\n";

  cout << "Prediction Results ~ Naive Bayes using Laplace Estimation\n";
  cout << *nb_lp_pd_set << "\n";
}
