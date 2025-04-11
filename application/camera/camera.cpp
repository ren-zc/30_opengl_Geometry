#include "camera.h"
#include "camera.h"
#include "camera.h"
#include "camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	// lookAt 
	// - eye: ���λ��(ʹ��mPostion)
	// - center: ������������ϵ���ĸ���
	// - top: 񷶥, ʹ��mUp����

	glm::vec3 front = glm::cross(mUp, mRight);
	glm::vec3 center = mPosition + front;
	return glm::lookAt(mPosition, center, mUp);

}

glm::mat4 Camera::getProjectiveMatrix()
{
	return glm::identity<glm::mat4>();
}

void Camera::scale(float yOffset)
{
}
