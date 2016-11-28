#ifdef _MSC_VER
// Disable warnings about unsafe functions (fopen et al)
#pragma warning(disable: 4996)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "thirdparty/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"