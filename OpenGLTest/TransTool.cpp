#include "TransTool.h"
#include "Eigen/Dense"
#include <cmath>
#include "CommonDefs.h"
GLMatrix::GLMatrix()
{
	mat = new Eigen::Matrix4f();
}

GLMatrix::GLMatrix(const Eigen::Matrix4f& m)
{
	mat = new Eigen::Matrix4f(m);
}

void GLMatrix::Identity()
{
	*mat = Eigen::Matrix4f::Identity();
}

float GLMatrix::AngleToArc(float angle) 
{
	using namespace expression;
	return angle*PI/180.f;
}

void GLMatrix::Translation(const Eigen::Vector3f& vec)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	tmp->block(0, 3, 3, 1) = vec;
	*mat = (*tmp) * (*mat);
	delete tmp;
}

void  GLMatrix::RotationWithAxis(float angle, const Eigen::Vector3f& vec)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	bool flag = true;
	float arc = GLMatrix::AngleToArc(angle);
	float cos_a = cos(arc);
	float sin_a = sin(arc);
	for (int i = 0; i <= 2&&flag; i++) {
		if (vec(i) != 0) 
		{
			if (i & 1)
			{
				(*mat)(0, 0) = (*mat)(2, 2) = cos_a;
				(*mat)(0, 2) = sin_a;
				(*mat)(2, 0) = -sin_a;
			}
			else
			{
				int next_cor = (i + 1) % 3;
				mat->block(next_cor, next_cor, 2, 2) <<
					cos_a, -sin_a, sin_a, cos_a;
			}
			flag = false;
		}
	}
}

float* GLMatrix::GLMatFormat() const {
	return &(*mat)(0);
}

GLMatrix::~GLMatrix()
{
	delete mat;
}
