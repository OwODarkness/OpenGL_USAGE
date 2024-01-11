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

float GLMatrix::ArcToAngle(float arc)
{
	using namespace expression;
	return arc * 180.0 / PI;
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
	delete tmp;
}

void GLMatrix::Scale(const Eigen::Vector3f& vec)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	for (int i = 0; i <= 2; i++)
	{
		(*tmp)(i, i) = vec(i);
	}
	*mat = (*tmp) * (*mat);
	delete tmp;
}

void  GLMatrix::EqualScale(float rate)
{
	this->Scale({rate, rate, rate});
}

void BaseTransform(const Eigen::Matrix3f& BaseMat)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	tmp->block(0, 0, 3, 3) = BaseMat;
}

void  GLMatrix::ViewPortTransform(float screen_w, float screen_h)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	(*tmp)(0, 0) = screen_w * 0.5f;
	(*tmp)(1, 1) = screen_h * 0.5f;
	tmp->block(0, 3, 2, 1) << (screen_w - 1.f) * 0.5f, (screen_h - 1.f) * 0.5f;
	*mat = (*tmp) * (*mat);
	delete tmp;
}

void GLMatrix::CameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f LookAtDir, const Eigen::Vector3f ViewUpDir)
{
	//Move To origin point
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	tmp->block(0, 3, 3, 1) = -Loc;
	*mat = (*tmp) * (*mat);

	//Rotate to the origin base axis
	*tmp = Eigen::Matrix4f::Identity();
	//x axis in camera coor
	Eigen::Vector3f* u = new Eigen::Vector3f();
	//y axis in camera coor
	Eigen::Vector3f* v = new Eigen::Vector3f();
	//z axis in camera coor
	Eigen::Vector3f* w = new Eigen::Vector3f();
	//orthonalization
	*w = -LookAtDir / LookAtDir.norm();
	Eigen::Vector3f* cross_tmp = new Eigen::Vector3f();
	*cross_tmp = ViewUpDir.cross(*w);
	*u = *cross_tmp / cross_tmp->norm();
	*v = w->cross(*u);
	tmp->block(0, 0, 3, 1) = *u;
	tmp->block(0, 1, 3, 1) = *v;
	tmp->block(0, 2, 3, 1) = *w;
	*mat = tmp->transpose() * (*mat);

	delete tmp;
	delete u;
	delete w;
	delete v;
	delete cross_tmp;
}

void GLMatrix::OrthProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	for (int i = 0; i <= 2; i++)
	{
		tmp[i][i] = 2 / (pot_rbn(i) - pot_ltf(i));
		tmp[i][3] = -0.5 * (pot_rbn(i) + pot_ltf(i));
	}
	*mat = (*tmp) * (*mat);

	delete tmp;
}
float* GLMatrix::GLMatFormat() const {
	return &(*mat)(0);
}

GLMatrix::~GLMatrix()
{
	delete mat;
}
