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
	//λ��
	void Translation(const Eigen::Vector3f& vec);
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
	//������任
	void CameraTransform(const Eigen::Vector3f& Loc, const Eigen::Vector3f LookAtDir, const Eigen::Vector3f ViewUpDir);
	//����ͶӰ
	void OrthProjection(const Eigen::Vector3f& pot_rbn, const Eigen::Vector3f& pot_ltf);
};
#endif // !TRANS_TOOL_H
