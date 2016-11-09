#ifndef __CRYSTAL_PHYSICS_PBSPH_NEIGHBOR_FINDER_H__
#define __CRYSTAL_PHYSICS_PBSPH_NEIGHBOR_FINDER_H__

#include "PBIndexedParticle.h"
#include <vector>
#include "ParticlePair.h"

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

		private:
			PBSPHParticle* particle1;
			PBSPHParticle* particle2;
		};

		class PBSPHNeighborFinder final : private UnCopyable
		{
		public:
			PBSPHNeighborFinder(const float effectLength) :
				effectLength(effectLength)
			{}

			void add(const std::vector<PBIndexedParticle>& particles);

			void add(const std::vector<PBSPHParticle*>& particles);

			void createPairs(std::vector<PBSPHParticle*> particles);

			std::vector<PBSPHParticlePair> getPairs() const { return pairs; }

			//std::list<SPHParticle*> find(const Math::Vector3d<float>& position);

		private:
			std::vector<PBSPHParticlePair> pairs;

			std::vector<PBSPHParticlePair> search1(const std::vector<PBIndexedParticle>& particles, std::vector<PBIndexedParticle>::const_iterator startIter, std::vector<PBIndexedParticle>::const_iterator endIter, const float effectLengthSquared);

			std::vector<PBSPHParticlePair> search2(const std::vector<PBIndexedParticle>& particles, std::vector<PBIndexedParticle>::const_iterator startIter, std::vector<PBIndexedParticle>::const_iterator endIter, const float effectLengthSquared);

			std::vector<PBIndexedParticle> iparticles;
			//std::vector<IndexedParticle> iparticlesy;
			//std::vector<IndexedParticle> iparticlesz;
			const float effectLength;
		};

	}
}


#endif