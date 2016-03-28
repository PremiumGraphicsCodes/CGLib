#ifndef __CRYSTAL_GRAPHICS_COLOR_MAP_H__
#define __CRYSTAL_GRAPHICS_COLOR_MAP_H__

#include <vector>
#include "ColorRGBA.h"
#include "../Util/UnCopyable.h"
#include <cassert>

namespace Crystal {
	namespace Graphics {

class Range
{
public:
	Range( const float min, const float max ) :
		min_( min ),
		max_( max )
	{
		assert( isValid() );
	}

	bool isValid() const { return min_ <= max_; }

	float getNormalized( const float value ) const {
		return ( value - min_ ) / ( max_ - min_ ); 
	}

	void setMin( const float m ) { min_ = m; }

	float getMin() const { return min_; }

	void setMax( const float m ) { max_ = m; }

	float getMax() const { return max_; }

private:
	float min_;
	float max_;
};

class ColorMap : private UnCopyable {
public:
	ColorMap();

	ColorMap(const float min, const float max, const int resolution);

	ColorMap(const std::vector<ColorRGBA<float> >& colors);

	void setColors(const std::vector<ColorRGBA<float> >& colors);

	void setColor(const size_t i, const Graphics::ColorRGBA<float>& c);

	bool isValid() const { 
		return
			( reds.size() == greens.size() ) &&
			( reds.size() == blues.size() ) &&
			( reds.size() == alphas.size() );
	}

	std::vector< float > getReds() const { return reds; }

	std::vector< float > getGreens() const { return greens; }

	std::vector< float > getBlues() const { return blues; }

	std::vector< float > getAlphas() const { return alphas; }

	int getResolution() const { return static_cast<int>(reds.size()); }

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	//float getNormalized( const float v ) const { return range.getNormalized( v ); }

	float getNormalized( const float value ) const {
		return ( value - min_ ) / ( max_ - min_ ); 
	}

	int getIndex( const float value ) const {
		return static_cast<int>( getNormalized(value) * ( getResolution() - 1 ) );
	}

	Graphics::ColorRGBA<float> getColorFromIndex(const int i) const {
		const auto r = reds[i];
		const auto g = greens[i];
		const auto b = blues[i];
		const auto a = alphas[i];
		return Graphics::ColorRGBA<float>( r, g, b, a );
	}

	Graphics::ColorRGBA<float> getColor(const float v) const {
		const int index = getIndex(v);
		return getColorFromIndex( index );
	}

	Graphics::ColorRGBA<float> getInterpolatedColor(const float v) const;

	float getValueFromIndex(const int i) const { 
		const float dt = (max_ - min_) / ( getResolution()-1);
		return ( dt * i + min_ );
	}

	void setMin( const float m ) {
		min_ = m;
		assert( isValid() );
	}

	float getMin() const { return min_; }

	void setMax( const float m ) {
		max_ = m;
		assert( isValid() );
	}

	float getMax() const { return max_; }

	void setMinMax( const float min__, const float max__ ) {
		this->min_ = min__;
		this->max_ = max__;
		assert( isValid() );
	}

	bool isValid() {
		return ( min_ <= max_ );
	}

	std::vector< ColorRGBA<float> > getColors() const {
		std::vector< ColorRGBA<float> > colors;
		for( size_t i = 0; i < reds.size(); ++i ) {
			colors.push_back( ColorRGBA<float>( reds[i], greens[i], blues[i], alphas[i] ) );
		}
		return colors;
	}

private:

	std::vector<float> reds;
	std::vector<float> greens;
	std::vector<float> blues;
	std::vector<float> alphas;

	float min_;
	float max_;

	std::string name;

	//int minValue;
	//int maxValue;
};

	}
}

#endif