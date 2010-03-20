#include <string>
using std::string;

#include <cstdlib>
#include <iostream>
using std::cout;

#include <simone/utility.h>

#include "classifier.h"
#include "dataset-parser.h"
#include "dataset-description.h"
#include "output-prediction-set.h"
using Radon::Classifier;
using Radon::OutputPredictionSet;

#include "naive-bayes/nb-classifier.h"
using Radon::NBClassifier;
using Radon::DatasetParser;
using Radon::DatasetDescription;

#include "logistic-regression/lr-classifier.h"
using Radon::LRClassifier;


namespace Radon {

/* dataset (e.g. "simple", "heart", "vote") */
const char *kDatasetDefault = "simple";

/* relative or absolute path where dataset files are located */
const char *kDatasetPath = "../datasets";

const uint32_t kDomainSize = 2;
const uint32_t kRangeSize = 2;

const char *kTestFlag = "-test";
const char *kTrainFlag = "-train";
const char *kExtension = ".txt";

} /* end of namespace Radon */

/* forward declarations */
int parse_command_line(int argc, char **argv, string &arg1, bool &help);
void print_help_message(const char *program_name);

int
main(int argc, char **argv) {
  bool help;
  string arg1;
  int ret = parse_command_line(argc, argv, arg1, help);
  if (ret != 0 || help) {
    print_help_message(argv[0]);
    return ret;
  }

  /* file path string declarations */
  string filepath_prefix, filepath_suffix;

  /* dataset declarations */
  DatasetDescription::PtrConst train_dataset, test_dataset;

  /* parse declaration */
  DatasetParser::PtrConst data_parser;

  /* classifier declarations:
     - Naive Bayes using Maximum Likelihood Estimation
     - Naive Bayes using Laplace Estimation
     - Logistic Regression */
  Classifier::Ptr nb_mle, nb_lp, lr;

  /* prediction declarations, one for each type of classifier */
  OutputPredictionSet::PtrConst nb_mle_pd_set, nb_lp_pd_set, lr_pd_set;

  /* building dataset file path */
  filepath_prefix =  Radon::kDatasetPath;
  filepath_prefix += "/";
  filepath_prefix += arg1;
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

  /* initializing Naive Bayes classifier using laplace estimation */
  nb_lp = NBClassifier::NBClassifierNew(train_dataset, NBClassifier::kLaplace);

  /* initializing Logistic Regression classifier */
  lr = LRClassifier::LRClassifierNew(train_dataset);

  /* assigning test datasets to classifiers */
  nb_mle->testDatasetIs(test_dataset);
  nb_lp->testDatasetIs(test_dataset);
  lr->testDatasetIs(test_dataset);

  /* computing predictions for both MLE and Laplace */
  nb_mle_pd_set = nb_mle->predictionSet();
  nb_lp_pd_set = nb_lp->predictionSet();
  lr_pd_set = lr->predictionSet();

  cout << "Prediction Results ~ Naive Bayes using MLE\n";
  cout << *nb_mle_pd_set << "\n";

  cout << "Prediction Results ~ Naive Bayes using Laplace Estimation\n";
  cout << *nb_lp_pd_set << "\n";

  cout << "Prediction Results ~ Logistic Regression\n";
  cout << *lr_pd_set << "\n";

  return 0;
}

int
parse_command_line(int argc, char **argv, string &arg1, bool &help) {
  int c;
  if ((c = getopt(argc, argv, "h")) != -1) {
    switch(c) {
      case 'h':
        /* (help) flag */
        help = true;
        return 0;
      default:
        /* error */
        return -1;
    }
  }

  if (optind < argc) {
    /* dataset-name is the first non-option argument */
    arg1 = argv[optind];
  } else {
    /* use default if none is specified */
    arg1 = Radon::kDatasetDefault;
  }

  if (optind + 1 < argc) {
    /* too many non-option arguments specified */
    return -1;
  }

  return 0;
}

void print_help_message(const char *program_name) {
  printf("usage: %s [dataset-name]\n\n", program_name);
  printf("Arguments:\n");
  printf("  [dataset-name]\n");
  printf("    Optional argument that specifies the dataset to be used.\n");
  printf("    Examples of valid values are: \"vote\", \"heart\", etc.\n");
  printf("    The default value of <dataset-name> is \"simple\"\n\n");
  printf("    Note that, for the time being, it is assumed that a\n");
  printf("    directory called datasets exists immediately above the\n");
  printf("    program's working directory, and that dataset filenames\n");
  printf("    are of the form \"<dataset-name>-<flag>.txt\" where\n");
  printf("    <flag> is either \"train\" or \"test\"\n\n");
  printf("Options:\n");
  printf("  -h  show this help message and exit\n\n");
}
