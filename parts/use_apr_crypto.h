#include "apu_version.h"
#if APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION < 4
#undef APU_MINOR_VERSION
#define APU_MINOR_VERSION	5
#define APU_HAVE_CRYPTO		1
#define APU_HAVE_OPENSSL	1
#define APU_HAVE_NSS		0
#endif
