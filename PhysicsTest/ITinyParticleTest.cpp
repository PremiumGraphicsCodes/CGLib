#include "gtest\gtest.h"
#include "../Physics/ITinyParticle.h"
#include "../Physics/PBSPHConstant.h"
#include "../Physics/PBSPHParticle.h"
#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

class ConcreteTinyParticle : public ITinyParticle
{
public:
	ConcreteTinyParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
		ITinyParticle(position, velocity, parent)
	{}

	void updateVelocity(const float dt, const Vector3d<float>& gravity) override
	{}
};

TEST(ITinyParticleTest, TestGetAveragedLocalVelocity)
{
	PBSPHConstant constant(1.0f, 0.0f, 1.0f);
	PBSPHParticle parent(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	BubbleParticle bp(&parent);
	PBSPHParticle neighbor(Vector3d<float>(0.5, 0, 0), 0.5, &constant);
	neighbor.setVelocity(Vector3d<float>(1.0, 0.0, 0.0));
	parent.setNeighbors({ &neighbor });

	ConcreteTinyParticle particle(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 0), &bp);
	EXPECT_EQ(Vector3d<float>(1,0,0), particle.getAveragedLocalVelocity());
}