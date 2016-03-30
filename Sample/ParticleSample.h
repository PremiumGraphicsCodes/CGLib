#ifndef __CRYSTAL_SAMPLE_PARTICLE_SAMPLE_H__
#define __CRYSTAL_SAMPLE_PARTICLE_SAMPLE_H__

#include "glfw.h"

#include "ISample.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/VolumeObject.h"
#include "../Polygon/PolygonObject.h"
#include <memory>

class ParticleSample : public ISample
{
public:
	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	std::unique_ptr<Crystal::Polygon::ParticleObject> particle;
	std::unique_ptr<Crystal::Polygon::VolumeObject> volume;
	std::unique_ptr<Crystal::Polygon::PolygonObject> polygon;
};

#endif