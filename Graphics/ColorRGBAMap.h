#ifndef __CRYSTAL_GRAPHICS_COLOR_RGBA_MAP_H__
#define __CRYSTAL_GRAPHICS_COLOR_RGBA_MAP_H__

#include <vector>
#include "ColorRGBA.h"
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

class NonCopyable
{
  protected:
    NonCopyable () {}
    ~NonCopyable () {}
  private: 
    NonCopyable (const NonCopyable &);
    NonCopyable & operator = (const NonCopyable &);
};

template<typename T>
class ColorRGBAMap : private NonCopyable {
public:
	ColorRGBAMap() :
		min_( 0.0f ),
		max_( 1.0f )
	{}

	ColorRGBAMap( const float min, const float max, const int resolution ) :
		min_( min ),
		max_( max ),
		reds( resolution ),
		greens( resolution ),
		blues( resolution ),
		alphas( resolution )
	{
		 assert( isValid() );
	}

	ColorRGBAMap( const std::vector<ColorRGBA<T> >& colors ) :
		min_( 0.0f ),
		max_( 1.0f )
	{
		setColors( colors );
	}

	void setColors( const std::vector<ColorRGBA<T> >& colors )
	{
		reds.clear();
		greens.clear();
		blues.clear();
		alphas.clear();
		for( const ColorRGBA<T>& c : colors ) {
			reds.push_back( c.getRed() );
			greens.push_back( c.getGreen() );
			blues.push_back( c.getBlue() );
			alphas.push_back( c.getAlpha() );
		}
	}
	

	/*
	void setResolution( const int resolution ) {
		image = Graphics::ImageRGBA<unsigned int>( 256, 1 );
	}
	*/

	void setColor( const size_t i, const Graphics::ColorRGBA<T>& c )
	{
		reds[i] = c.getRed();
		greens[i] = c.getGreen();
		blues[i] = c.getBlue();
		alphas[i] = c.getAlpha();
	}

	bool isValid() const { 
		return
			( reds.size() == greens.size() ) &&
			( reds.size() == blues.size() ) &&
			( reds.size() == alphas.size() );
	}

	std::vector< T > getReds() const { return reds; }

	std::vector< T > getGreens() const { return greens; }

	std::vector< T > getBlues() const { return blues; }

	std::vector< T > getAlphas() const { return alphas; }

	int getResolution() const { return static_cast<int>(reds.size()); }

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	//float getNormalized( const float v ) const { return range.getNormalized( v ); }

	float getNormalized( const T value ) const {
		return ( value - min_ ) / ( max_ - min_ ); 
	}

	int getIndex( const float value ) const {
		return static_cast<int>( getNormalized(value) * ( getResolution() - 1 ) );
	}

	Graphics::ColorRGBA<T> getColorFromIndex(const int i) const {
		const T r = reds[i];
		const T g = greens[i];
		const T b = blues[i];
		const T a = alphas[i];
		return Graphics::ColorRGBA<T>( r, g, b, a );
	}

	Graphics::ColorRGBA<T> getColor(const float v) const {
		const int index = getIndex(v);
		return getColorFromIndex( index );
	}

	Graphics::ColorRGBA<T> getInterpolatedColor(const float v) const {
		if( v <= min_ ) {
			return Graphics::ColorRGBA<T>( reds.front(), greens.front(), blues.front(), alphas.front() );// getColor( min_ );
		}
		if( v >= max_ ) {
			return Graphics::ColorRGBA<T>( reds.back(), greens.back(), blues.back(), alphas.back() );
			//return getColor( max_ );
		}
		const int index1 = getIndex(v);
		const int index2 = getIndex(v)+1;

		if( index1 < 0 ) {
		}
		if( index2 >= getResolution() ) {
			return getColor( max_ );
		}
		const float v1 = getValueFromIndex( index1 );
		const float v2 = getValueFromIndex( index2 );

		Range range( v1, v2 );
		const float ratio = range.getNormalized( v );

		Graphics::ColorRGBA<T> c1 = getColorFromIndex( index1 ).getScaled( ratio );
		Graphics::ColorRGBA<T> c2 = getColorFromIndex( index2 ).getScaled( 1.0f - ratio );
		return c1 + c2;
	}

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

	std::vector< ColorRGBA<T> > getColors() const {
		std::vector< ColorRGBA<T> > colors;
		for( size_t i = 0; i < reds.size(); ++i ) {
			colors.push_back( ColorRGBA<T>( reds[i], greens[i], blues[i], alphas[i] ) );
		}
		return colors;
	}

private:

	std::vector<T> reds;
	std::vector<T> greens;
	std::vector<T> blues;
	std::vector<T> alphas;

	float min_;
	float max_;

	std::string name;

	//int minValue;
	//int maxValue;
};

	}
}

#endif