#include "gtest/gtest.h"

#include "../Math/MarchingCube.h"

#include "Volume3d.h"

using namespace Crystal::Math;

using TestTypes = ::testing::Types <
	std::tuple< float, float >,
	std::tuple< float, double >
>;

template<class T>
class MarchingCubeTest : public testing::Test {
};


TYPED_TEST_CASE(MarchingCubeTest, TestTypes);

TYPED_TEST(MarchingCubeTest, TestMarchScalarSpace)
{
	using GeomType = std::tuple_element<0, TypeParam>::type;
	using ValueType = std::tuple_element<1, TypeParam>::type;


	MarchingCube<GeomType, ValueType> mc;

	Space3d<GeomType> s(Vector3d<GeomType>(0, 0, 0), Vector3d<GeomType>(10, 10, 10));
	const Grid3d<ValueType> grid(2,2,2);
	Volume3d<GeomType, ValueType> ss(s, grid);

	mc.march(ss, 1);
}