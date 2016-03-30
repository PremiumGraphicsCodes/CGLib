#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class IDRenderer : public IRenderer
{
public:
	IDRenderer() = default;

	~IDRenderer() = default;

	void findLocation() override;

	void render(const Graphics::ICamera<float>& camera) override;

	bool buildBuildInShader();

private:
	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;


	std::vector<float> positions;
	std::vector<float> ids;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
	};

	Location location;

};
	}
}

#endif