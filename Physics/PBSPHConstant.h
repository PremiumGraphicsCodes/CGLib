#ifndef __CRYSTAL_PHYSICS_PBSPH_CONSTANT_H__
#define __CRYSTAL_PHYSICS_PBSPH_CONSTANT_H__

namespace Crystal {
	namespace Physics {

class PBSPHConstant
{
public:
	PBSPHConstant() :
		viscosityCoe(0.0f),
		effectLength(1.25f),
		density(1000.0f)
	{
	}

	PBSPHConstant(const float density, const float viscosityCoe, const float effectLength) :
		density(density),
		viscosityCoe(viscosityCoe),
		effectLength(effectLength)
	{
	}

	float getDensity() const { return density; }

	float getViscosityCoe() const { return viscosityCoe; }

	float getEffectLength() const { return effectLength; }

private:
	float viscosityCoe;
	float effectLength;
	float density;
};

	}
}

#endif