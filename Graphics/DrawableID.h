#ifndef __CRYSTAL_GRAPHICS_DRAWABLE_ID_H__
#define __CRYSTAL_GRAPHICS_DRAWABLE_ID_H__

#include "../Core/UID.h"

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

	explicit DrawableID(const ColorRGBA<float>& c);

	explicit DrawableID(const ColorRGBA<unsigned char>& c);

	void fromColor(const ColorRGBA<float>& c);

	void fromColor(const ColorRGBA<unsigned char>& c);

	ColorRGBA<float> toColor() const;
	
	unsigned int toUInt() const { return id.to_ulong(); }

	bool equals(const DrawableID& rhs) const { return this->id == rhs.id; }

	bool operator==(const DrawableID& rhs) const { return equals(rhs); }

	bool operator!=(const DrawableID& rhs) const { return !equals(rhs); }

private:
	std::bitset<32> id;
};

	}
}

#endif