#include "nb-classifier.h"

#include "frequency-table.h"
#include "globals.h"
#include "nb-prediction-set.h"

namespace Radon {

NBClassifier::NBClassifier(DatasetDescription::PtrConst training_data) :
  Classifier(training_data)
{
  FrequencyTable::Ptr freq_table;
  JointDistTable::Ptr joint_dist_table;
  Observation in_value, out_value;
  for (uint32_t var = 0; var < training_data_->varCount(); ++var) {
    /* creating frequency table for singlge variable */
    freq_table = FrequencyTable::FrequencyTableNew(kDomainSize, kRangeSize);

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
}

PredictionSet::PtrConst
NBClassifier::predictionSet(EstMode _mode) {
  if (prediction_set_ != NULL)
    return prediction_set_;

  prediction_set_ = NBPredictionSet::NBPredictionSetNew(_mode);

  if (test_data_ == NULL)
    return prediction_set_;

  return compute_prediction_set(_mode);
}

PredictionSet::PtrConst
NBClassifier::compute_prediction_set(EstMode _mode) {

}

} /* end of namespace Radon */
