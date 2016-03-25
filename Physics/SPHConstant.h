#ifndef __CRYSTAL_PHYSICS_SPH_CONSTANT_H__
#define __CRYSTAL_PHYSICS_SPH_CONSTANT_H__

namespace Crystal {
	namespace Physics {

class SPHConstant
{
public:
	SPHConstant() :
		pressureCoe(1.0f),
		viscosityCoe(0.0f),
		tensionCoe(0.0f),
		effectLength(1.25f),
		density(1000.0f),
		isBoundary(false)
	{
	}

	SPHConstant(const float density, const float pressureCoe, const float viscosityCoe, const float tensionCoe, const float effectLength) :
		density(density),
		pressureCoe(pressureCoe),
		viscosityCoe(viscosityCoe),
		tensionCoe(tensionCoe),
		effectLength(effectLength),
		isBoundary(false)
	{
	}
	
	float getDensity() const { return density; }

	float getPressureCoe() const { return pressureCoe; }

	float getViscosityCoe() const { return viscosityCoe; }

	float getTensionCoe() const { return tensionCoe; }

	float getEffectLength() const { return effectLength; }

	bool isBoundary;

private:
	float pressureCoe;
	float viscosityCoe;
	float tensionCoe;
	float effectLength;
	float density;
};

	}
}

#endif