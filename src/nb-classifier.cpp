#include "nb-classifier.h"

#include "frequency-table.h"
#include "globals.h"
#include "nb-prediction-set.h"

namespace Radon {

/* constructor trains learning algorithm with TRAINING_DATA */
NBClassifier::NBClassifier(DatasetDescription::PtrConst training_data) :
  Classifier(training_data), domain_size_(kDomainSize), range_size_(kRangeSize)
{
  FrequencyTable::Ptr freq_table;
  JointDistTable::Ptr joint_dist_table;
  Observation in_value, out_value;

  /* generating joint probability distribution tables for each variable */
  for (uint32_t var = 0; var < training_data_->varCount(); ++var) {
    /* creating frequency table for singlge variable */
    freq_table = FrequencyTable::FrequencyTableNew(domain_size_, range_size_);

    /* populating frequency table by tracking
       occurences througout every data vector */
    for (uint32_t vec = 0; vec < training_data_->vectorCount(); ++vec) {
      in_value = training_data_->inputObservation(vec, var);
      out_value = training_data_->outputObservation(vec);

      /* incrementing frequency at coorditates
         (in_value, out_value) of frequency table */
      freq_table->frequencyInc(in_value.value(), out_value.value());
    }

    /* converting frequency table into a joint probability distribution table */
    joint_dist_table = JointDistTable::JointDistTableNew(freq_table);

    /* adding distribution table to model */
    joint_dist_.pushBack(joint_dist_table);
  }

  /* populating vector of output marginal probabilities, P(Y) */
  for (uint32_t out_idx = 0; out_idx < range_size_; ++out_idx)
    out_marginal_.pushBack(joint_dist_[0]->outputMarginal(out_idx));
}

PredictionSet::PtrConst
NBClassifier::predictionSet(EstMode _mode) {
  /* if a prediction set for test_data_ has
     already been computed and is cached, return it */
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = NBPredictionSet::NBPredictionSetNew(_mode);

  /* if test_data_ is NULL, return an empty prediction */
  if (test_data_ == NULL)
    return prediction_set_;

  return prediction_set(_mode);
}

PredictionSet::PtrConst
NBClassifier::prediction_set(EstMode _mode) {
  return NULL;
}

ProbabilityLn
NBClassifier::input_cond_ln_product(uint32_t in_val, uint32_t out_condition) {
  JointDistTable::Ptr joint_dist;
  Probability p;
  ProbabilityLn p_ln;

  for (uint32_t dist_idx = 0; dist_idx < joint_dist_.size(); ++dist_idx) {
    /* joint probability distribution for variable X_i */
    joint_dist = joint_dist_[dist_idx];

    /* Probability p = P(X_i | Y) */
    Probability p = joint_dist->inputConditional(in_val, out_condition);

    /* ProbabilityLn p_ln = ln(p) */
    p_ln += ProbabilityLn(p);
  }

  return p_ln;
}

} /* end of namespace Radon */
