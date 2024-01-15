#pragma once

#include "Eigen/Core" 

class Camera
{
public:
	Camera():Camera::Camera({0.f, 0.f, -3.f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f}){}
	Camera(const Eigen::Vector3f& Loc, const Eigen::Vector3f& Target, const Eigen::Vector3f& Up) :
		Location(Loc)
	{
		CameraUp << 0.f, 1.f, 0.f;
		CameraForward << 0.f, 0.f, 1.f;
		LookAt = CameraForward;
		LookUp = CameraUp;
	}
	inline Eigen::Vector3f GetCameraLocation() const {return Location;}
	inline Eigen::Vector3f GetLookAtDirection() const { return LookAt; }
	inline Eigen::Vector3f GetLookUpDirection() const { return LookUp; }
	inline void SetCameraSpeed(float Value) { this->CameraSpeed = Value; }
	void MoveForward(float Value);
	void MoveBackward(float Value);
	void MoveUp(float Value);
	void MoveDown(float Value);
	void MoveRight(float Value);
	void  MoveLeft(float Value);
private:
	Eigen::Vector3f Location;
	Eigen::Vector3f LookAt;
	Eigen::Vector3f LookUp;
	Eigen::Vector3f CameraUp;
	Eigen::Vector3f CameraForward;
	float CameraSpeed = 1.f;
	//float fov;
};

