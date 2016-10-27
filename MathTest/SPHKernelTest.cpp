#include "gtest\gtest.h"

#include "../Math/SPHKernel.h"

using namespace Crystal::Math;

TEST(SPHKernelTest, TestGetPoly6Kernel)
{
	SPHKernel<float> kernel;
	EXPECT_EQ(0.0f, kernel.getPoly6Kernel(1.1f, 1.0f));
}

TEST(SPHKernelTest, TestGetPoly6KernelGradient)
{
	SPHKernel<float> kernel;
	EXPECT_EQ(Vector3d<float>(0,0,0), kernel.getPoly6KernelGradient(Vector3d<float>(1.1f, 0.0f, 0.0f), 1.0f));
}

TEST(SPHKernelTest, TestGetPoly6KernelLaplacian)
{
	SPHKernel<float> kernel;
	EXPECT_EQ(0.0f, kernel.getPoly6KernelLaplacian(1.1f, 1.0f));
}

TEST(SPHKernelTest, TestGetSpikyKernelGradient)
{
	SPHKernel<float> kernel;
	EXPECT_EQ(Vector3d<float>(0,0,0), kernel.getSpikyKernelGradient(Vector3d<float>(1.1f, 0.0, 0.0), 1.0f));
}


TEST(SPHKernelTest, TestGetCubicSpiline)
{
	SPHKernel<float> kernel;
	{
		const auto actual = kernel.getCubicSpline(0);
		const auto expected = 1.0f / Tolerance<float>::getPI();
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(1);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(2);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
}

TEST(SPHKernelTest, TestGetCubicSpilineWithEffectRadius)
{
	SPHKernel<float> kernel;
	{
		const auto actual = kernel.getCubicSpline(0, 1.0f);
		const auto expected = 1.0f / Tolerance<float>::getPI();
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(0.5f, 1.0f);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(1.0f, 1.0f);
		const auto expected = 0.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

}

TEST(SPHKernelTest, TestGetCubicSpilineByVector)
{
	SPHKernel<float> kernel;
	{
		const auto actual = kernel.getCubicSpline(Vector3d<float>(1, 0, 0), 1.0f);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(Vector3d<float>(2, 0, 0), 1.0f);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

	{
		const auto actual = kernel.getCubicSpline(Vector3d<float>(2, 0, 0), 2.0f);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI()) / 8;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

}

TEST(SPHKernelTest, TestGetCubicSpilineByMatrix)
{
	SPHKernel<float> kernel;
	{
		Matrix3d<float> matrix;
		const auto actual = kernel.getCubicSpline(Vector3d<float>(0.5, 0, 0), matrix);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		Matrix3d<float> matrix;
		const auto actual = kernel.getCubicSpline(Vector3d<float>(1.0, 0, 0), matrix);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

	{
		Matrix3d<float> matrix = Vector3d<float>(0.5, 0.5, 0.5).toDiagonalMatrix();
		const auto actual = kernel.getCubicSpline(Vector3d<float>(1, 0, 0), matrix);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI()) / 8;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
}

TEST(SPHKernelTest, TestGetCubicSplineGradient)
{
	using T = float;
	SPHKernel<T> kernel;

	{
		Vector3d<T> v(0, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v);
	}
	
	{
		Vector3d<T> v(0.25, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v);
		const auto v1 = kernel.getCubicSpline(0.25f);
		const auto v2 = kernel.getCubicSpline(0.25f + 1.0e-4f);
		const auto diff = (v2 - v1) / 1.0e-4f;

		EXPECT_TRUE(::fabs(diff - grad.getX())<1.0e-3f);
	}

	{
		Vector3d<T> v(0.5, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v);
		std::cout << grad.getX() << std::endl;
		const auto v1 = kernel.getCubicSpline(0.5f);
		const auto v2 = kernel.getCubicSpline(0.5f + 1.0e-4f);
		const auto diff = (v2 - v1) / 1.0e-4f;
		EXPECT_TRUE(::fabs(diff - grad.getX())<1.0e-3f);

	}

	{
		Vector3d<T> v(0.75, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v);
		const auto v1 = kernel.getCubicSpline(0.75f);
		const auto v2 = kernel.getCubicSpline(0.75f + 1.0e-4f);
		const auto diff = (v2 - v1) / 1.0e-4f;
		EXPECT_TRUE(::fabs(diff - grad.getX())<1.0e-3f);

	}

	{
		Vector3d<T> v(1, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v);

		const auto v1 = kernel.getCubicSpline(1);
		const auto v2 = kernel.getCubicSpline(1 + 1.0e-4f);
		const auto diff = (v2 - v1) / 1.0e-4f;

	}
}

TEST(SPHKernelTest, TestGetCubicSplineGradientWithEffectRadius)
{
	using T = float;
	SPHKernel<T> kernel;
	const T effectRadius = 1.0f;
	{
		Vector3d<T> v(0, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v, effectRadius);
		const auto v1 = kernel.getCubicSpline(0.0, effectRadius);
		const auto v2 = kernel.getCubicSpline(0.0f + 1.0e-4f, effectRadius);
		const auto diff = (v2 - v1) / 1.0e-4;
		std::cout << diff << std::endl;
	}

	/*
	{
		Vector3d<T> v(0.5, 0, 0);
		const auto& grad = kernel.getCubicSplineGradient(v, effectRadius);
		const auto v1 = kernel.getCubicSpline(0.5f, effectRadius);
		const auto v2 = kernel.getCubicSpline(0.5f + 1.0e-4f, effectRadius);
		const auto diff = (v2 - v1) / 1.0e-4f;

		EXPECT_TRUE(::fabs(diff - grad.getX()) < 1.0e-3f);
	}
	*/
}