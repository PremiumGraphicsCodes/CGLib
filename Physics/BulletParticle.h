#ifndef __CRYSTAL_PHYSICS_BULLET_MAP_H__
#define __CRYSTAL_PHYSICS_BULLET_MAP_H__

#include <vector>

namespace Crystal {
	namespace Physics {

class PhysicsObject;
class BulletRigid;
class SPHParticle;

class BulletParticle
{
public:
	BulletParticle() :
		rigid(nullptr)
	{}

	BulletParticle(const std::vector<SPHParticle*>& particles) :
		rigid(nullptr),
		particles(particles)
	{}

	BulletParticle(BulletRigid* rigid) :
		rigid(rigid)
	{}

	BulletParticle(BulletRigid* rigid, const std::vector<SPHParticle*>& particles) :
		rigid(rigid),
		particles(particles)
	{}

	std::vector<SPHParticle*> getParticles() const { return particles; }

private:
	BulletRigid* rigid;
	std::vector<SPHParticle*> particles;

};

	}
}

#endif