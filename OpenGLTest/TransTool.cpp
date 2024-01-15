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
	return angle*(float)PI/180.f;
}

float GLMatrix::ArcToAngle(float arc)
{
	using namespace expression;
	return arc * 180.0f / (float)PI;
}

void GLMatrix::Translation(const Eigen::Vector3f& vec)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	tmp->block(0, 3, 3, 1) = vec;
	*mat = (*tmp) * (*mat);
	if (debug_flag)
	{
		Debug(*tmp, "Translation");
	}
	delete tmp;
}

void GLMatrix::SetLocation(const Eigen::Vector3f& vec)
{
	mat->block(0, 3, 3, 1) = vec;
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
				(*tmp)(0, 0) = (*tmp)(2, 2) = cos_a;
				(*tmp)(0, 2) = sin_a;
				(*tmp)(2, 0) = -sin_a;
			}
			else
			{
				int next_cor = (i + 1) % 3;
				tmp->block(next_cor, next_cor, 2, 2) <<
					cos_a, -sin_a, sin_a, cos_a;
			}
			flag = false;
		}
	}
	(*mat) = (*tmp) * (*mat);
	if (debug_flag)
	{
		Debug(*tmp, "Rotation");
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

void GLMatrix::CameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir, const Eigen::Vector3f& ViewUpDir)
{
	//Move To origin point
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(GetCameraTransformationMatrix(Loc, LookAtDir, ViewUpDir));
	*mat = (*tmp) * (*mat);
	if (debug_flag)
	{
		Debug(*tmp, "View Transformation");
	}
	delete tmp;
}

void GLMatrix::SetCameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir, const Eigen::Vector3f& ViewUpDir)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(GetCameraTransformationMatrix(Loc, LookAtDir, ViewUpDir));

	if (debug_flag)
	{
		Debug(*tmp, "View Transformation");
	}
	*mat = *tmp;
	delete tmp;
}

void GLMatrix::OrthProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());
	for (int i = 0; i <= 2; i++)
	{
		(*tmp)(i, 3) = -0.5f * (pot_rbn(i) + pot_ltf(i));
	}
	
	Eigen::Matrix4f* tmp2 = new Eigen::Matrix4f(Eigen::Matrix4f::Identity());

	for (int i = 0; i <= 2; i++)
	{
		(*tmp2)(i, i) = 2.f / abs(pot_rbn(i) - pot_ltf(i));
	}
	*mat = (*tmp2) * (*tmp) * (*mat);
	if (debug_flag)
	{
		Debug(*tmp, "OthoT1");
		Debug(*tmp2, "OthoT2");

	}
	(*mat)(3, 2) = -1;
	delete tmp;
}

void  GLMatrix::PerProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf)
{
	Eigen::Matrix4f* tmp = new Eigen::Matrix4f();
	tmp->setZero();
	(*tmp)(0, 0) = (*tmp)(1, 1) = abs(pot_rbn(2));//n
	(*tmp)(2, 2) = pot_rbn(2) + pot_ltf(2);//n+f
	(*tmp)(2, 3) = -pot_rbn(2) * pot_ltf(2);//-nf
	(*tmp)(3, 2) = 1;
	*mat = (*tmp) * (*mat);
	if (debug_flag)
	{
		Debug(*tmp, "Perspective to Orthographic");
	}
	delete tmp;
	OrthProjection(pot_rbn, pot_ltf);
}

void  GLMatrix::PerProjection(float FOV, float aspect_radio, float near, float far)
{
	using namespace constval;
	near *= -1.f;
	far *= -1.f;
	float top = abs(near) * tan(AngleToArc(0.5*FOV));
	float bottom = -top;
	float right = top * aspect_radio;
	float left = -right;
	PerProjection({right, bottom, near}, {left, top, far});
}


float* GLMatrix::GLMatFormat() const {
	
	return mat->data();
}

GLMatrix::~GLMatrix()
{
	delete mat;
}

void GLMatrix::Debug(const Eigen::Matrix4f& m, std::string debug_message)
{
	if (!debug_message.empty())
	{
		std::cout << debug_message << std::endl;
	}
	std::cout  << m << std::endl;
}

Eigen::Matrix4f GLMatrix::GetCameraTransformationMatrix(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir, const Eigen::Vector3f& ViewUpDir)
{
	Eigen::Matrix4f tmp1 = Eigen::Matrix4f::Identity();
	tmp1.block(0, 3, 3, 1) = -Loc;
	//Rotate to the origin base axis
	Eigen::Matrix4f tmp2 = Eigen::Matrix4f::Identity();

	//x axis in camera coor	*tmp = Eigen::Matrix4f::Identity();
	Eigen::Vector3f u;
	//y axis in camera coor
	Eigen::Vector3f v;
	//z axis in camera coor
	Eigen::Vector3f w;
	//orthonalization
	w = -LookAtDir / LookAtDir.norm();
	Eigen::Vector3f cross_tmp;
	cross_tmp = ViewUpDir.cross(w);
	u = cross_tmp / cross_tmp.norm();
	v = w.cross(u);
	tmp2.block(0, 0, 3, 1) = u;
	tmp2.block(0, 1, 3, 1) = v;
	tmp2.block(0, 2, 3, 1) = w;

	return tmp2.transpose() * tmp1;
}
