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
	void Translation(const Eigen::Vector3f& vec);
	void RotationWithAxis(float angle, const Eigen::Vector3f& vec);

	static float AngleToArc(float angle);
};
#endif // !TRANS_TOOL_H
