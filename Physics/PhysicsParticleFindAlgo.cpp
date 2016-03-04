#include "PhysicsParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

template<typename GeomType>
void ParticleFindAlgo<GeomType>::createPairs(std::vector<Particle*> particles, const GeomType effectLength)
{
	if (particles.empty()) {
		return;
	}

	for (const auto& particle : particles) {
		particle->setGridID(effectLength);
	}

	std::sort(particles.begin(), particles.end(), &Particle::compare);

	// optimization for quad core.
	const int threads = 8;

	std::vector<std::vector<ParticlePair>> eachPairs(threads);

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

template<typename GeomType>
std::vector<ParticlePair> ParticleFindAlgo<GeomType>::search1(const std::vector<Particle*>& particles, std::vector<Particle*>::const_iterator startIter, std::vector<Particle*>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<ParticlePair> pairs;
	for (auto xIter = startIter; xIter != endIter; ++xIter) {
		const auto gridID = (*xIter)->getGridID();
		const auto& centerX = (*xIter)->getPosition();
		auto yIter = xIter;
		++yIter;// ignore itself.
		while (yIter != particles.end() && ((*yIter)->getGridID() <= gridID + 1)) {
			const auto& centerY = (*yIter)->getPosition();
			if (centerX.getDistanceSquared(centerY) < effectLengthSquared) {
				pairs.push_back(ParticlePair((*xIter), (*yIter)));
				pairs.push_back(ParticlePair((*yIter), (*xIter)));
			}
			++yIter;
		}
	}
	return pairs;
}

template<typename GeomType>
std::vector<ParticlePair> ParticleFindAlgo<GeomType>::search2(const std::vector<Particle*>& particles, std::vector<Particle*>::const_iterator startIter, std::vector<Particle*>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<ParticlePair> pairs;

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

			const auto& centerX = (*xIter)->getPosition();
			auto zIter = yIter[i];
			while (zIter != particles.end() && ((*zIter)->getGridID() <= baseID + 2)) {
				const auto& centerZ = (*zIter)->getPosition();
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



template class ParticleFindAlgo<float>;