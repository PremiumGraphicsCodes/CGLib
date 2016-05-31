#ifndef __CRYSTAL_PHYSICS_BULLET_RIGID_H__
#define __CRYSTAL_PHYSICS_BULLET_RIGID_H__

#include <vector>

#include "Bullet.h"

#include "../Math/Vector3d.h"
#include "../Math/Box3d.h"
#include "../Math/Sphere.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix4d.h"
#include "Surfels.h"
#include "SPHConstant.h"
#include "../Core/PolygonMesh.h"

class btRigidBody;

namespace Crystal {
	namespace Physics {
		class SPHParticle;

		class BulletRigid
		{
		public:
			BulletRigid(const Math::Box3d<float>& box, SPHConstant* constant, const unsigned int id = -1, Core::PolygonMesh* shape = nullptr);

	//BulletRigid(const Math::Sphere<float>& sphere, const float mass);

	BulletRigid(btRigidBody* body, const unsigned int id = -1) :
		id(id),
		body(body),
		shape(nullptr)
	{}

	~BulletRigid();

	void clear();

	float getMass() const;

	void setVelocity(const Math::Vector3d<float>& v);

	Math::Vector3d<float> getOrigin() const;

	Math::Quaternion<float> getOrientation() const;

	Math::Matrix4d<float> getTransformMatrix() const;

	btRigidBody* getBody() const { return body; }

	void transform();

	void solveBoundary();

	Math::Vector3d<float> getAngleVelocity() const;

	std::vector<SPHParticle*> getSurfaceParticles();

	void move(const Math::Vector3d<float>& v);

	void addForce(const Math::Vector3d<float>& v);

	Math::Box3d<float> getLocalShape() const { return localBox; }

	unsigned int getId() const { return id; }

	void setShape(Core::PolygonMesh* shape) { this->shape = shape; }

	Core::PolygonMesh* getShape() const { return this->shape; }

private:
	btRigidBody* body;
	Math::Box3d<float> localBox;
	std::vector<Math::Vector3d<float>> localPositions;
	std::vector<SPHParticle*> sampleParticles;
	Core::PolygonMesh* shape;
	const unsigned int id;
};

	}
}

#endif