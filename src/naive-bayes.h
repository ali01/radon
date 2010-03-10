#ifndef NAIVE_BAYES_H_KJPCTBNX
#define NAIVE_BAYES_H_KJPCTBNX

#include <simone/ptr_interface.h>

namespace Radon {

class NaiveBayesClassifier : public Simone::PtrInterface<NaiveBayesClassifier> {
public:
  typedef Simone::Ptr<const NaiveBayesClassifier> PtrConst;
  typedef Simone::Ptr<NaiveBayesClassifier> Ptr;
  
  static Ptr NaiveBayesClassifierNew() { return new NaiveBayesClassifier(); }

private:
  NaiveBayesClassifier() {}
  
  /* disallowed operations */
  NaiveBayesClassifier(const NaiveBayesClassifier&);
  NaiveBayesClassifier& operator=(const NaiveBayesClassifier&);
};

} /* end of namespace Radon */

#endif
