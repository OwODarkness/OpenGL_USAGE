#pragma once
#include <cmath>



namespace constval {
	constexpr double PI = 3.14159265358979323846;
	constexpr double e = 2.71828182845904523536;
	constexpr double sqrt2 = 1.41421356237309504880;
	constexpr double sqrt3 = 1.73205080756887729352;
	constexpr double golden_ratio = 1.61803398874989484820;
}
namespace expression {
	using namespace constval;
	double cos_45 = cos(PI / 4);
	double sin_45 = sin(PI / 4);
	double cos_30 = cos(PI / 6);
	double sin_30 = sin(PI / 6);
	double cos_60 = cos(PI / 3);
	double sin_60 = sin(PI / 3);
}
namespace gldef {
	constexpr unsigned int SCR_WIDTH = 1600;
	constexpr unsigned int SCR_HEIGHT = 1200;
}

