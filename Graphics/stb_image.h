#ifndef __CRYSTAL_IMAGE_STB_IMAGE_H__
#define __CRYSTAL_IMAGE_STB_IMAGE_H__

namespace stb {

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image.h"

#define STB_IMAGE_RESIZE_STATIC
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image_resize.h"

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image_write.h"

}

#endif
