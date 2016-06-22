#ifndef __CRYSTAL_BILLBOARD_RENDERER_H__
#define __CRYSTAL_BILLBOARD_RENDERER_H__

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class BillBoardRenderer final : public IRenderer
{
public:
	BillBoardRenderer() :
		pointSizeX( 100 ),
		pointSizeY( 100 )
	{}

	BillBoardRenderer(const ShaderObject& shader):
		IRenderer(shader),
		pointSizeX( 100 ),
		pointSizeY( 100 )
	{}

	~BillBoardRenderer() = default;

	void findLocation() override;

	void render(const Graphics::ICamera<float>& camera) override;

	void changeSize(const float x, const float y) {
		this->pointSizeX = x;
		this->pointSizeY = y;
	}

private:
	float pointSizeX;
	float pointSizeY;
};

	}
}

#endif