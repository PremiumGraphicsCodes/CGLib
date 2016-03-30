#include "IRenderer.h"

#include <gl/GL.h>

using namespace Crystal::Shader;

bool IRenderer::build(const std::string& vSource, const std::string& gSource, const std::string& fSource)
{
	return shader.build(vSource, gSource, fSource);
}
