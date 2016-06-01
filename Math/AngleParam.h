#ifndef __CRYSTAL_MATH_ANGLE_PARAM_H__
#define __CRYSTAL_MATH_ANGLE_PARAM_H__


namespace Crystal {
	namespace Math {

		template<typename T>
		class Param;

		template<typename T>
		class AngleParam
		{
		public:
			AngleParam();

			explicit AngleParam(T param);

			Param<T> toParam() const;

		private:
			bool isValid() const;

			T param;
		};

	}

}
#endif