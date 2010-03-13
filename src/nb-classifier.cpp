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

/* returns the natural log of the probability P(X,Y) = P(X | Y) * P(Y) where
   X = INPUT_VECTOR and Y = OUTPUT_VALUE. Note that, because the Naive Bayes
   assumption, P(X | Y) is approximated by the product over all P(X_i | Y)
   or the sum of their logs. */
ProbabilityLn
NBClassifier::joint_prob_ln(DatasetDescription::PtrConst _dataset,
                            uint32_t _input_vector,
                            Observation _output_value) const {
  JointDistTable::Ptr joint_dist;
  Observation in_val;
  Probability p;

  /* initialized with a probability of 1.0; ln(1.0) = 0 */
  ProbabilityLn p_ln(1.0);

  /* iterate over the joint probability distribution of each variable,
     compute the variable's conditional probability P(X_i | Y), and add
     it's log into p_ln. */
  for (uint32_t dist_idx = 0; dist_idx < joint_dist_.size(); ++dist_idx) {
    /* joint probability distribution for variable X_i */
    joint_dist = joint_dist_[dist_idx];

    /* input value X_i at the specified INPUT_VECTOR in DATASET */
    in_val = _dataset->inputObservation(_input_vector, dist_idx);

    /* Probability p = P(X_i | Y) */
    p = joint_dist->inputConditional(in_val, _output_value);

    /* increment P_LN by ln(P) */
    p_ln += ProbabilityLn(p);
  }

  /* P_LN is currently equal to the sum of the natural logs of P(X_i | Y)
     for all i. Multiply P_LN by the log of the marginal probability of Y. */
  p = joint_dist->outputMarginal(_output_value);
  p_ln *= ProbabilityLn(p);

  return p_ln;
}

/* for a given INPUT_VECTOR in DATASET, returns the value of OUTPUT_VALUE
   that yields the maximum return value possible when passed into
   joint_prob_ln() */
Observation
NBClassifier::joint_prob_arg_max(DatasetDescription::PtrConst _dataset,
                                 uint32_t _input_vector) const {
  Observation arg_max;

  /* initialized with a probability of 0.0; ln(0.0) = DOUBLE_MIN */
  ProbabilityLn p_max(0.0), curr(0.0);

  /* iterate over possible return values of input_cond_ln_product and
     keep track of maximum */
  for (uint32_t out_cond; out_cond < range_size_; ++out_cond) {
    curr = joint_prob_ln(_dataset, _input_vector, out_cond);
    if (curr > p_max){
      arg_max = out_cond;
      p_max = curr;
    }
  }

  return arg_max;
}

} /* end of namespace Radon */
