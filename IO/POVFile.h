#ifndef __CRYSTAL_IO_POV_FILE_H__
#define __CRYSTAL_IO_POV_FILE_H__

#include "../Util/File.h"
#include "../Graphics/Surface.h"

namespace Crystal {
	namespace IO {

class POVFile
{
public:
	bool write(const File& file, const Graphics::Surface<float>& surface);
private:

};
	}
}

#endif