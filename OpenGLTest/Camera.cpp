#include "Camera.h"

void Camera::MoveForward(float Value)
{
	Location += Value * CameraSpeed * CameraForward;
}

void Camera::MoveBackward(float Value)
{
	Location -= Value * CameraSpeed * CameraForward;

}

void Camera::MoveUp(float Value)
{
	Location += Value * CameraSpeed * CameraUp;

}

void Camera::MoveDown(float Value)
{
	Location -= Value * CameraSpeed * CameraUp;
}

void Camera::MoveRight(float Value)
{
	Location += Value * CameraSpeed * CameraUp.cross(CameraForward).normalized();

}

void Camera::MoveLeft(float Value)
{
	Location -= Value * CameraSpeed * CameraUp.cross(CameraForward).normalized();

}
