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

	DrawableID(const unsigned int id, const unsigned char type);

	explicit DrawableID(const ColorRGBA<float>& c);

	explicit DrawableID(const ColorRGBA<unsigned char>& c);

	void fromColor(const ColorRGBA<float>& c);

	void fromColor(const ColorRGBA<unsigned char>& c);

	ColorRGBA<float> toColor() const;

	//ColorRGBA<unsigned char> toColorUC() const;
	
	//unsigned int toUInt() const { return id.to_ulong(); }

	bool equals(const DrawableID& rhs) const {
		return this->id == rhs.id &&
			this->type == rhs.type;
	}

	bool operator==(const DrawableID& rhs) const { return equals(rhs); }

	bool operator!=(const DrawableID& rhs) const { return !equals(rhs); }

	unsigned char getType() const;

	unsigned int getValue() const;

private:
	std::bitset<24> id;
	std::bitset<8> type;
};

	}
}

#endif