#ifndef __CRYSTAL_SHADER_LEGACY_VOLUME_RENDERER_H__
#define __CRYSTAL_SHADER_LEGACY_VOLUME_RENDERER_H__

#include "GLee.h"

#include "../Graphics/PointBuffer.h"
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Shader {

		class LegacyVolumeRenderer
		{
		public:
			void render(Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

		private:

		};
	}
}

#endif