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
	float mLeft = 0.0f;  // 相对于摄像机本地坐标系
	float mRight = 0.0f;  // 相对于摄像机本地坐标系
	float mTop = 0.0f;  // 相对于摄像机本地坐标系
	float mBottom = 0.0f;  // 相对于摄像机本地坐标系
	float mNear = 0.0f;  // 相对于摄像机本地坐标系
	float mFar = 0.0f;  // 相对于摄像机本地坐标系

	float mScale = 0.0f; // 缩放比例累加值
};
