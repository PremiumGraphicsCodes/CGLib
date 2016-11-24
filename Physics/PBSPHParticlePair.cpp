#include "PBSPHParticlePair.h"
#include "PBSPHParticle.h"

using namespace Crystal::Physics;

void PBSPHParticlePair::solveDensity()
{
	particle1->addDensity(*particle2);
	particle2->addDensity(*particle1);
}

void PBSPHParticlePair::solveConstrantGradient()
{
	particle1->solveConstrantGradient(*particle2);
	particle2->solveConstrantGradient(*particle1);
}

void PBSPHParticlePair::solveDensityConstraint()
{
}

void PBSPHParticlePair::solvePositionCorrection()
{
	;
}

void PBSPHParticlePair::solveNormal()
{
	particle1->solveNormal(*particle2);
	particle2->solveNormal(*particle1);
}
