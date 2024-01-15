#ifndef TRANS_TOOL_H
#define  TRANS_TOOL_H
#include <iostream>
#include "Eigen/Core"
#include <string>
class GLMatrix {
private:
	Eigen::Matrix4f* mat;
	bool debug_flag = false;
public:
	GLMatrix();
	GLMatrix(const Eigen::Matrix4f& m);
	~GLMatrix();
	void Identity();
	float* GLMatFormat() const;
	//位移
	void Translation(const Eigen::Vector3f& vec);
	//指定位置
	void SetLocation(const Eigen::Vector3f& vec);
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
	//摄像机变换 View Transform
	void CameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir = Eigen::Vector3f(0,0,1), const Eigen::Vector3f& ViewUpDir = Eigen::Vector3f(0, 1, 0));
	void SetCameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir, const Eigen::Vector3f& ViewUpDir);
	//正交投影 
	void OrthProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf);
	//透视投影 
	void PerProjection(float FOV, float aspect_radio, float near, float far);
	void  PerProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf);
	
	void SetDebugflag(bool flag) { this->debug_flag = flag; }

	Eigen::Matrix4f GetMat() const { return *mat; }

public:
	static void Debug(const Eigen::Matrix4f& m, std::string debug = "");

private:
	Eigen::Matrix4f GetCameraTransformationMatrix(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir, const Eigen::Vector3f& ViewUpDir);
};
#endif // !TRANS_TOOL_H
