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
	static ColorRGBA<ColorType> toRGB(const ColorHSV<ColorType>& hsv) {
		const auto h = hsv.getH();
		const auto s = hsv.getS();
		const auto v = hsv.getV();

		const auto max = v;
		const auto min = max - (s / 1.0f) * max;

		if (0 <= h && h <= 60) {
			const auto g = h / 60.0f * (max - min) + min;
			return ColorRGBA<ColorType>(max, g, min).getScaled(255);
		}
		else if (h <= 120.0f) {
			const auto r = (120.0f - h) / 60.0f * (max - min) + min;
			return ColorRGBA<ColorType>(r, max, min).getScaled(255);
		}
		else if (h <= 180.0f) {
			const auto b = (h - 120.0f) / 60.0f * (max - min) + min;
			return ColorRGBA<ColorType>(min, max, b).getScaled(255);
		}
		else if (h <= 240.0f) {
			const auto g = (240.0f - h) / 60.0f * (max - min) + min;
			return ColorRGBA<ColorType>(min, g, max).getScaled(255);
		}
		else if (h <= 300.0f) {
			const auto r = (h - 240.0f) / 60.0f * (max - min) + min;
			return ColorRGBA<ColorType>(r, min, max).getScaled(255);
		}
		else if (h <= 360.0f) {
			const ColorType b = (360.0f - h) / 60.0f * (max - min) + min;
			return ColorRGBA<ColorType>(max, min, b).getScaled(255);
		}
		else {
			assert(false);
			return ColorRGBA<ColorType>::Black();
		}
	}

	static ColorHSV<ColorType> toHSV(const ColorRGBA<ColorType>& rgb) {
		const auto r = rgb.getRed() / ColorType{ 255 };
		const auto g = rgb.getGreen() / ColorType{ 255 };
		const auto b = rgb.getBlue() / ColorType{ 255 };

		const auto min = std::min<ColorType>(r, std::min<ColorType>(g, b));
		const auto max = std::max<ColorType>(r, std::max<ColorType>(g, b));

		const auto v = max;
		const auto s = max - min;

		if (min == max) {
			const ColorType h = 0.0;
			return ColorHSV<ColorType>(h, s, v);
		}
		else if (min == b) {
			const ColorType h = 60.0f * (g - r) / (max - min) + 60.0f;
			return ColorHSV<ColorType>(h, s, v);
		}
		else if (min == r) {
			const auto h = 60.0f * (b - g) / (max - min) + 180.0f;
			return ColorHSV<ColorType>(h, s, v);
		}
		else if (min == g) {
			const auto h = 60.0f * (r - b) / (max - min) + 300.0f;
			return ColorHSV<ColorType>(h, s, v);
		}
		else {
			assert(false);
			return ColorHSV<ColorType>();
		}

	}

	static ColorType toGrayScale(const ColorRGBA<ColorType>& rgb) {
		const auto g =  77 * rgb.getRed() + 150 * rgb.getGreen() + 29 * rgb.getBlue();
		return g / ColorType{255};
	}

};
	}
}

#endif