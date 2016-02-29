#include "Spring.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Spring::Spring(const ParticlePair& pair, const Param param) :
	pair(pair),
	param(param)
{}

void Spring::proceedTime(const float dt)
{
	const auto diff =  pair.getDistance() - param.restDistance;
	const auto force = diff * param.springCoe * pair.getDistanceVector();
	pair.getParticle1()->addForce(force);
	pair.getParticle2()->addForce(-force);
}