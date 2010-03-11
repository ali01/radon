#include "nb-classifier.h"

#include "frequency-table.h"
#include "globals.h"
#include "nb-prediction-set.h"

namespace Radon {

NBClassifier::NBClassifier(DatasetDescription::PtrConst training_data) :
  Classifier(training_data)
{
  FrequencyTable::Ptr freq_table;
  Observation var_value, output_value;
  for (uint32_t var = 0; var < training_data_->varCount(); ++var) {
    /* creating frequency table for singlge variable */
    freq_table = FrequencyTable::FrequencyTableNew(kNumVarValues,
                                                   kNumOutputValues);
    /* populating frequency table by tracking
       occurences througout every data vector */
    for (uint32_t vec = 0; vec < training_data_->vectorCount(); ++vec) {
      var_value = training_data_->inputObservation(vec, var);
      output_value = training_data_->outputObservation(vec);
      freq_table->frequencyInc(var_value.value(), output_value.value());
    }

    /* converting frequency table into a joint probability distribution table */

    // dist_map_.pushBack(freq_table);
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
