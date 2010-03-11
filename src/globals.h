#ifndef GLOBALS_H_MZFRZ076
#define GLOBALS_H_MZFRZ076

#include <stdint.h>

namespace Radon {

/* dataset (e.g. "simple", "heart", "vote") */
extern const char *kDataset;

extern const char *kDatasetPath;

extern const char *kTestFlag;
extern const char *kTrainFlag;
extern const char *kExtension;

extern const uint32_t kDomainSize;
extern const uint32_t kRangeSize;

} /* end of namespace Radon */

#endif
