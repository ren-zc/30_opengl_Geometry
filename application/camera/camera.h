#pragma once

#include "../../glframwork/core.h"

class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 getViewMatrix();  // �����ͼ����

	virtual glm::mat4 getProjectiveMatrix();  // ͶӰ����

	virtual void scale(float yOffset);

public:
	glm::vec3 mPosition{ 0.0f, 0.0f, 5.0f };  // �������������ϵ�µ�λ��(����)
	glm::vec3 mUp{ 0.0f, 1.0f, 0.0f };  // �������������ϵ�µ�up����(����)
	glm::vec3 mRight{ 1.0f, 0.0f, 0.0f };  // �������������ϵ�µ�right����(����)

private:
	
};
