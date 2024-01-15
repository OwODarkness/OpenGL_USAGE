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
	//λ��
	void Translation(const Eigen::Vector3f& vec);
	//ָ��λ��
	void SetLocation(const Eigen::Vector3f& vec);
	//������ת
	void RotationWithAxis(float angle, const Eigen::Vector3f& vec);
	//����
	void Scale(const Eigen::Vector3f& vec);
	//�ȱ�����
	void EqualScale(float rate);
	//�Ƕ�ת����
	static float AngleToArc(float angle);
	//����ת�Ƕ�
	static float ArcToAngle(float arc);
	//�ӿڱ任
	void ViewPortTransform(float screen_w, float screen_h);
	//������任 View Transform
	void CameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir = Eigen::Vector3f(0,0,1), const Eigen::Vector3f& ViewUpDir = Eigen::Vector3f(0, 1, 0));
	void SetCameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f& LookAtDir, const Eigen::Vector3f& ViewUpDir);
	//����ͶӰ 
	void OrthProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf);
	//͸��ͶӰ 
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
