#pragma once
#include "camera.h"

class OrthographicCamera: public Camera
{
public:
	OrthographicCamera(float l, float r, float t, float b, float n, float f);
	~OrthographicCamera();

	glm::mat4 getProjectiveMatrix() override;

	void scale(float yOffset) override;

private:
	float mLeft = 0.0f;  // ������������������ϵ
	float mRight = 0.0f;  // ������������������ϵ
	float mTop = 0.0f;  // ������������������ϵ
	float mBottom = 0.0f;  // ������������������ϵ
	float mNear = 0.0f;  // ������������������ϵ
	float mFar = 0.0f;  // ������������������ϵ

	float mScale = 0.0f; // ���ű����ۼ�ֵ
};
