#include "nb-classifier.h"

#include "frequency-table.h"
#include "globals.h"
#include "prediction-set.h"

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
NBClassifier::predictionSet() {
  /* if a prediction set for test_data_ has
     already been computed and is cached, return it */
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = PredictionSet::PredictionSetNew();

  /* if test_data_ is NULL, return an empty prediction */
  if (test_data_ == NULL)
    return prediction_set_;

  compute_prediction_set();

  return prediction_set_;
}

void
NBClassifier::compute_prediction_set() const {

}

/* returns the product, in log space, over all P(X_i=x, Y)
   where x = IN_VAL and Y = out_condition */
ProbabilityLn
NBClassifier::input_cond_ln_product(DatasetDescription::PtrConst _dataset,
                                    uint32_t _data_vector,
                                    Observation _out_condition) const {
  JointDistTable::Ptr joint_dist;
  Observation in_val;
  Probability p;

  /* initialized with a probability of 1.0 -- ln(1.0) = 0 */
  ProbabilityLn p_ln(1.0);

  /* iterate over the joint probability distribution of each variable, compute the
     variable's conditional probability P(X_i | Y), and add it's log into p_ln. */
  for (uint32_t dist_idx = 0; dist_idx < joint_dist_.size(); ++dist_idx) {
    /* joint probability distribution for variable X_i */
    joint_dist = joint_dist_[dist_idx];

    /* input value X_i at the specified DATA_VECTOR in DATASET */
    in_val = _dataset->inputObservation(_data_vector, dist_idx);

    /* Probability p = P(X_i | Y) */
    p = joint_dist->inputConditional(in_val, _out_condition);

    /* ProbabilityLn p_ln = ln(p) */
    p_ln += ProbabilityLn(p);
  }

  return p_ln;
}

uint32_t
NBClassifier::output_arg_max() const {
  return 0;
}

} /* end of namespace Radon */
