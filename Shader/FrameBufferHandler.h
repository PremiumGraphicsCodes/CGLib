#ifndef __CRYSTAL_SHADER_FRAME_BUFFER_HANDLER_H__
#define __CRYSTAL_SHADER_FRAME_BUFFER_HANDLER_H__

#include "../Util/UnCopyable.h"
#include "FrameBuffer.h"
#include <map>

namespace Crystal {
	namespace Shader {

class FrameBufferHandler : private UnCopyable
{
public:
	static FrameBufferHandler* getInstance() {
		static FrameBufferHandler instance;
		return &instance;
	}

	~FrameBufferHandler() {
		clear();
	}

	void clear() {
		for (auto t : map) {
			delete t.second;
		}
		map.clear();
	}

	bool has(const std::string& name) {
		return map.find(name) != map.end();
	}

	FrameBuffer* get(const std::string& name) { return map[name]; }

private:
	FrameBufferHandler() = default;

	std::map<std::string, FrameBuffer* > map;
};

	}
}

#endif