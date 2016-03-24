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
		effectLength(1.25f)
	{
	}

	SPHConstant(const float pressureCoe, const float viscosityCoe, const float tensionCoe, const float effectLength) :
		pressureCoe(pressureCoe),
		viscosityCoe(viscosityCoe),
		tensionCoe(tensionCoe),
		effectLength(effectLength)
	{
	}

	float getPressureCoe() const { return pressureCoe; }

	float getViscosityCoe() const { return viscosityCoe; }

	float getTensionCoe() const { return tensionCoe; }

	float getEffectLength() const { return effectLength; }

private:
	float pressureCoe;
	float viscosityCoe;
	float tensionCoe;
	float effectLength;
};

	}
}

#endif