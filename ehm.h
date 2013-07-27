#ifndef __EHM_H__
#define __EHM_H__

#define CHECK_BOOL(val) if (!val) {goto Error;}
#define CHECK_BOOL_EX(val, message) if (!val) {std::cerr << message << endl; goto Error; }

#define CHECK_NULL(val) if (val == NULL) {goto Error;}
#define CHECK_NULL_EX(val, message) if (val == NULL) {std::cerr << message << endl; goto Error; }

#endif
