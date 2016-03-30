#ifndef __CRYSTAL_GRAPHICS_DRAWABLE_ID_H__
#define __CRYSTAL_GRAPHICS_DRAWABLE_ID_H__

namespace Crystal {
	namespace Graphics {
		template<typename>
		class ColorRGBA;

class DrawableID
{
public:
	explicit DrawableID(const unsigned int id) :
		id(id)
	{}

	ColorRGBA<float> toColor() const;

	unsigned int toUInt() const { return id; }

private:
	const unsigned int id;
};

	}
}

#endif