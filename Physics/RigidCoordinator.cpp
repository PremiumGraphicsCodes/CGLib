#include "RigidCoordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void RigidCoordinator::coordinate(const std::vector<Particle*>& particles)
{
	const Math::Vector3d<float>& objectCenter = getCenter(particles);
	const Math::Vector3d<float>& velocityAverage = getAverageVelosity(particles);

	for (const auto& p : particles) {
		p->setVelocity(velocityAverage);
	}

	for (const auto& p : particles) {
		p->addCenter(-1.0 * objectCenter);
	}

	//std::cout << getCenter( particles ).x << std::endl;
	//std::cout << getCenter( particles ).y << std::endl;
	//std::cout << getCenter( particles ).z << std::endl;

	//assert( getCenter( particles ) == Math::Vector3d( 0.0, 0.0, 0.0 ) );

	Math::Vector3d<float> inertiaMoment(0.0, 0.0, 0.0);
	Math::Vector3d<float> torque(0.0, 0.0, 0.0);

	for (const auto& particle : particles) {
		const auto& center = particle->getCenter();

		Math::Vector3d<float> particleMoment(pow(center.getY(), 2) + pow(center.getZ(), 2),
			pow(center.getZ(), 2) + pow(center.getX(), 2),
			pow(center.getX(), 2) + pow(center.getY(), 2));
		inertiaMoment += (particleMoment)* particle->getMass();

		const Math::Vector3d<float> diffVector(Math::Vector3d<float>(0.0, 0.0, 0.0), particle->getCenter());
		const Math::Vector3d<float>& particleTorque = diffVector.getOuterProduct(particle->getForce() * particle->getVolume());
		torque += particleTorque;
	}

	getAngleVelosity(inertiaMoment, torque, proceedTime);

	if (Math::Tolerance<float>::isEqualStrictly(angleVelosity.getLength())) {
		for (const auto& p : particles) {
			p->addCenter(objectCenter);
		}
		convertToFluidForce(particles);
		return;
	}
	const float rotateAngle = angleVelosity.getLength() * proceedTime;
	if (rotateAngle < 1.0e-5) {
		for (const auto& p : particles) {
			p->addCenter(objectCenter);
		}
		convertToFluidForce(particles);
		return;
	}

	Math::Quaternion<float> quaternion(angleVelosity.getNormalized(), rotateAngle);
	const Math::Matrix3d<float>& rotateMatrix = quaternion.toMatrix();
	/*	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
	(*iter)->variable.center.rotate( rotateMatrix );
	}

	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
	(*iter)->variable.center += objectCenter;
	} */
	convertToFluidForce(particles);

}
