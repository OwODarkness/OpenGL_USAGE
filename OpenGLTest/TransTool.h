#ifndef TRANS_TOOL_H
#define  TRANS_TOOL_H
#include "Eigen/Core"

class GLMatrix {
private:
	Eigen::Matrix4f* mat;
public:
	GLMatrix();
	GLMatrix(const Eigen::Matrix4f& m);
	~GLMatrix();
	void Identity();
	float* GLMatFormat() const;
	//位移
	void Translation(const Eigen::Vector3f& vec);
	//绕轴旋转
	void RotationWithAxis(float angle, const Eigen::Vector3f& vec);
	//缩放
	void Scale(const Eigen::Vector3f& vec);
	//等比缩放
	void EqualScale(float rate);
	//角度转弧度
	static float AngleToArc(float angle);
	//弧度转角度
	static float ArcToAngle(float arc);
	//视口变换
	void ViewPortTransform(float screen_w, float screen_h);
	//摄像机变换
	void CameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f LookAtDir, const Eigen::Vector3f ViewUpDir);
	//正交投影
	void OrthProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf);
};
#endif // !TRANS_TOOL_H
