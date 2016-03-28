#ifndef __CRYSTAL_GRAPHICS_COLOR_CONVERTER_H__
#define __CRYSTAL_GRAPHICS_COLOR_CONVERTER_H__

#include <algorithm>


#include "ColorHSV.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

template<typename ColorType>
class ColorConverter {
public:

	static ColorHSV toHSV(const ColorRGBA<ColorType>& rgb) {
		const auto r = rgb.getRed() / ColorType{ 255 };
		const auto g = rgb.getGreen() / ColorType{ 255 };
		const auto b = rgb.getBlue() / ColorType{ 255 };

		const auto min = std::min<ColorType>(r, std::min<ColorType>(g, b));
		const auto max = std::max<ColorType>(r, std::max<ColorType>(g, b));

		const auto v = max;
		const auto s = max - min;

		if (min == max) {
			const ColorType h = 0.0;
			return ColorHSV(h, s, v);
		}
		else if (min == b) {
			const ColorType h = 60.0f * (g - r) / (max - min) + 60.0f;
			return ColorHSV(h, s, v);
		}
		else if (min == r) {
			const auto h = 60.0f * (b - g) / (max - min) + 180.0f;
			return ColorHSV(h, s, v);
		}
		else if (min == g) {
			const auto h = 60.0f * (r - b) / (max - min) + 300.0f;
			return ColorHSV(h, s, v);
		}
		else {
			assert(false);
			return ColorHSV();
		}

	}


};
	}
}

#endif