#pragma once

#include "PBSPHParticle.h"
#include "../Math/Vector3d.h"
#include "../Math/Index3d.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

		class PBIndexedParticle
		{
		public:
			PBIndexedParticle() :
				particle(nullptr)
			{}

			PBIndexedParticle(PBSPHParticle* particle) :
				particle(particle)
			{
			}

		public:
			void setGridID(const float effectLength);

			Math::Vector3d<float> getPosition() const { return particle->getPosition(); }

			static int toGridId(const Math::Vector3d<float> pos, const float effectLength);

			static Math::Index3d toIndex(const Math::Vector3d<float> pos, const float effectLength);

			int getGridID() const { return gridID; }

			bool operator<(const PBIndexedParticle& rhs) {
				return this->getGridID() < rhs.getGridID();
			}

			PBSPHParticle* getParticle() const { return particle; }

		private:
			static int toIdX(Math::Index3d index);

		private:
			PBSPHParticle* particle;
			int gridID;
		};
	}
}