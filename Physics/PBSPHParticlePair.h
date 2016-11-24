#pragma once

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

class PBSPHParticlePair
{
public:
	PBSPHParticlePair(PBSPHParticle* p1, PBSPHParticle* p2) :
		particle1(p1),
		particle2(p2)
	{}

	void solveDensity();
	
	void solveConstrantGradient();
	
	void solveDensityConstraint();
	
	void solvePositionCorrection();

	void solveNormal();

	PBSPHParticle* getParticle1() { return particle1; }

	PBSPHParticle* getParticle2() { return particle2; }

private:
	PBSPHParticle* particle1;
	PBSPHParticle* particle2;
};


	}
}