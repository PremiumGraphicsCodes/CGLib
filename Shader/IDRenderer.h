#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType, typename ValueType, typename ColorType>
class IDRenderer : public IRenderer<GeomType>
{
public:
	IDRenderer() = default;

	~IDRenderer() = default;

	void render(const Graphics::ICamera<GeomType>& camera) override;

private:
	std::vector<GeomType> positions;
	std::vector<ValueType> ids;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
	};

	Location getLocations(const Crystal::Shader::ShaderObject& shader);

};
	}
}

#endif