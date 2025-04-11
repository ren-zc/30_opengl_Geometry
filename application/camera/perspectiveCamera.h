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
	// 相机坐标系下的数据, 摄像机看向-z轴
	float mFovy = 0.0f;  // 角度
	float mAspect = 0.0f;
	float mNear = 0.0f; // 正数, 近平面, 相机坐标系下距离相机的近平面距离
	float mFar = 0.0f;	// 正数, 远平面, 相机坐标系下距离相机的远平面距离
};
