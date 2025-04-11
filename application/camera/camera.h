#pragma once

#include "../../glframwork/core.h"

class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 getViewMatrix();  // 相机视图矩阵

	virtual glm::mat4 getProjectiveMatrix();  // 投影矩阵

	virtual void scale(float yOffset);

public:
	glm::vec3 mPosition{ 0.0f, 0.0f, 5.0f };  // 相机在世界坐标系下的位置(坐标)
	glm::vec3 mUp{ 0.0f, 1.0f, 0.0f };  // 相机在世界坐标系下的up方向(向量)
	glm::vec3 mRight{ 1.0f, 0.0f, 0.0f };  // 相机在世界坐标系下的right方向(向量)

private:
	
};
