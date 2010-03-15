#include "nb-classifier.h"

#include "frequency-table.h"
#include "output-prediction-set.h"

namespace Radon {

/* constructor trains learning algorithm with TRAINING_DATA */
NBClassifier::NBClassifier(DatasetDescription::PtrConst training_data,
                           size_t _domain_size, size_t _range_size,
                           EstMode _mode) :
  Classifier(training_data, _domain_size, _range_size)
{
  FrequencyTable::Ptr freq_table;
  JointDistTable::Ptr joint_dist_table;
  Observation in_value, out_value;

  /* generating joint probability distribution tables for each variable */
  for (uint32_t var = 0; var < training_data_->varCount(); ++var) {
    /* creating frequency table for single variable;
       if MODE is equal to laplace, initialize frequency table values to 1
       rather than to 0 */
    Frequency init_freq = (_mode == kLaplace) ? Frequency(1) : Frequency(0);
    freq_table = FrequencyTable::FrequencyTableNew(domain_size_, range_size_,
                                                   init_freq);

    // TODO: refactor to use DataInstance
    /* populating frequency table by tracking
       occurences throughout every data vector */
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

  /* populating vector of output marginal probabilities, P(Y);
     all joint probability distribution tables should have the same P(Y) */
  for (uint32_t out_idx = 0; out_idx < range_size_; ++out_idx)
    out_marginal_.pushBack(joint_dist_[0]->outputMarginal(out_idx));
}

/* overrides pure virtual function in base class;
   computes an output prediction for the given input vector INSTANCE */
Observation
NBClassifier::prediction(DataInstance::PtrConst _instance) const {
  /* computing the value that maximizes the joint probability P(X, Y) */
  return joint_prob_arg_max(_instance);;
}

/* for a given input vector INSTANCE, returns the value of OUTPUT_VALUE
   that yields the maximum return value possible when passed into
   joint_prob_ln() */
Observation
NBClassifier::joint_prob_arg_max(DataInstance::PtrConst _instance) const {
  Observation arg_max;

  /* initialized with a probability of 0.0; ln(0.0) = DOUBLE_MIN */
  ProbabilityLn p_max(0.0), curr(0.0);

  /* iterate over possible return values of input_cond_ln_product and
     keep track of maximum */
  for (uint32_t out_cond = 0; out_cond < range_size_; ++out_cond) {
    curr = joint_prob_ln(_instance, out_cond);
    if (curr > p_max){
      arg_max = out_cond;
      p_max = curr;
    }
  }

  return arg_max;
}

/* returns the natural log of the probability P(X,Y) = P(X | Y) * P(Y) where
   X = INSTANCE and Y = OUTPUT_VALUE. Note that, because of the Naive Bayes
   assumption, P(X | Y) is approximated by the product over all P(X_i | Y)
   or the sum of their logs. */
ProbabilityLn
NBClassifier::joint_prob_ln(DataInstance::PtrConst _instance,
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

    /* input value X_i in INSTANCE */
    in_val = _instance->inputObservation(dist_idx);

    /* Probability p = P(X_i | Y) */
    p = joint_dist->inputConditional(in_val, _output_value);

    /* if p is equal to 0.0, the entire product will be equal to zero. */
    if (p == Probability(0.0)) {
      /* log of zero is -Inf or DOUBLE_MIN */
      p_ln = ProbabilityLn(p);
      break;
    }

    /* increment P_LN by ln(P) */
    p_ln += ProbabilityLn(p);
  }

  /* P_LN is currently equal to the sum of the natural logs of P(X_i | Y)
     for all i. Increment P_LN by the log of the marginal probability of Y. */
  p = joint_dist->outputMarginal(_output_value);
  p_ln += ProbabilityLn(p);

  return p_ln;
}

} /* end of namespace Radon */
