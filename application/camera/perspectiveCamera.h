#pragma once
#include "camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fovy, float aspect, float near, float far);
	~PerspectiveCamera();

	glm::mat4 getProjectiveMatrix() override;
	void scale(float yOffset) override;

private:
	// �������ϵ�µ�����, ���������-z��
	float mFovy = 0.0f;  // �Ƕ�
	float mAspect = 0.0f;
	float mNear = 0.0f; // ����, ��ƽ��, �������ϵ�¾�������Ľ�ƽ�����
	float mFar = 0.0f;	// ����, Զƽ��, �������ϵ�¾��������Զƽ�����
};
