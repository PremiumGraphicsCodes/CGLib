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
	//particle1->solveDensityConstraint(particle2);
	;
}

void PBSPHParticlePair::solvePositionCorrection()
{
	;
}


