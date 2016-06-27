#ifndef __CRYSTAL_SHADER_LINE_ID_RENDERER_H__
#define __CRYSTAL_SHADER_LINE_ID_RENDERER_H__

#include "IRenderer.h"
#include "../Graphics/LineIdBuffer.h"

namespace Crystal {
	namespace Shader {

		class LineIdRenderer
		{
		public:
			LineIdRenderer() = default;

			~LineIdRenderer() = default;

			void set(ShaderObject* shader);

			void render(const Graphics::ICamera<float>& camera, const Graphics::LineIdBuffer& buffer, const int width);

			bool build();

		private:
			std::string getBuildinVertexShaderSource() const;

			std::string getBuildinFragmentShaderSource() const;

			ShaderObject* shader;

		};
	}
}

#endif