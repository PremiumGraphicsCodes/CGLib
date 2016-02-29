#ifndef __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__

#include "Particle.h"
#include "ParticlePair.h"

#include "../Util/UnCopyable.h"

#include <vector>
#include <algorithm>

#ifdef _OPENMP
#include <omp.h>
#endif


namespace Crystal{
	namespace Physics{

template<typename GeomType>
class ParticleFindAlgo final : private UnCopyable{
public:
	ParticleFindAlgo() = default;

	~ParticleFindAlgo() = default;

	void createPairs(std::vector<Particle*> particles, const GeomType effectLength) {
		if (particles.empty()) {
			return;
		}

		for (const auto& particle : particles) {
			particle->setGridID(effectLength);
		}

		std::sort(particles.begin(), particles.end(), &Particle::compare);

		// optimization for quad core.
		const int threads = 8;

		std::vector<ParticlePairVector> eachPairs(threads);

		std::vector<std::vector<Particle*>::const_iterator> iters;
		for (int i = 0; i < threads; ++i) {
			iters.push_back(particles.begin() + i * particles.size() / threads);
		}
		iters.push_back(particles.end());

		#pragma omp parallel for
		for (int i = 0; i < threads; ++i) {
			eachPairs[i] = search1(particles, iters[i], iters[i + 1], effectLength * effectLength);
		}

		for (size_t i = 0; i < eachPairs.size(); ++i) {
			pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
		}

		#pragma omp parallel for
		for (int i = 0; i < threads; ++i) {
			eachPairs[i] = search2(particles, iters[i], iters[i + 1], effectLength * effectLength);
		}

		for (size_t i = 0; i < eachPairs.size(); ++i) {
			pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
		}

	}

	ParticlePairVector getPairs() const { return pairs; }

private:
	ParticlePairVector pairs;

	ParticlePairVector search1(const std::vector<Particle*>& particles, std::vector<Particle*>::const_iterator startIter, std::vector<Particle*>::const_iterator endIter, const float effectLengthSquared) {
		ParticlePairVector pairs;
		for (auto xIter = startIter; xIter != endIter; ++xIter) {
			const auto gridID = (*xIter)->getGridID();
			const auto& centerX = (*xIter)->getCenter();
			auto yIter = xIter;
			++yIter;// ignore itself.
			while (yIter != particles.end() && ((*yIter)->getGridID() <= gridID + 1)) {
				const auto& centerY = (*yIter)->getCenter();
				if (centerX.getDistanceSquared(centerY) < effectLengthSquared) {
					pairs.push_back(ParticlePair((*xIter), (*yIter)));
					pairs.push_back(ParticlePair((*yIter), (*xIter)));
				}
				++yIter;
			}
		}
		return pairs;
	}

	ParticlePairVector search2(const std::vector<Particle*>& particles, std::vector<Particle*>::const_iterator startIter, std::vector<Particle*>::const_iterator endIter, const float effectLengthSquared) {
		ParticlePairVector pairs;

		std::vector<std::vector<Particle*>::const_iterator> yIter(4, startIter);
		std::vector<int> offsetIds;
		offsetIds.push_back(1023);
		offsetIds.push_back(1047551);
		offsetIds.push_back(1048575);
		offsetIds.push_back(1049599);

		for (std::vector<Particle*>::const_iterator xIter = startIter; xIter != endIter; ++xIter) {
			for (size_t i = 0; i < 4; ++i) {
				const auto baseID = (*xIter)->getGridID() + offsetIds[i];
				while (yIter[i] != particles.end() && ((*yIter[i])->getGridID() < baseID)) {
					++yIter[i];
				}

				const auto& centerX = (*xIter)->getCenter();
				auto zIter = yIter[i];
				while (zIter != particles.end() && ((*zIter)->getGridID() <= baseID + 2)) {
					const auto& centerZ = (*zIter)->getCenter();
					if (centerX.getDistanceSquared(centerZ) < effectLengthSquared) {
						pairs.push_back(ParticlePair((*xIter), (*zIter)));
						pairs.push_back(ParticlePair((*zIter), (*xIter)));
					}
					++zIter;
				}
			}
		}

		return pairs;

	}
};

	}
}

#endif