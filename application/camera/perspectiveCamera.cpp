#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far): mFovy(fovy), mAspect(aspect), mNear(near), mFar(far)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getProjectiveMatrix()
{
	// fovy: y轴视张角, 弧度单位, float类型
    // aspect: 近平面的横纵百分比: 宽/高, 再次为800/600
    // near: 相机坐标系下进平面距离(正数, 虽然位于-z方向)
    // far: 相机坐标系下远平面距离

    // mFovy是角度, 应该转换为弧度
    return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}

void PerspectiveCamera::scale(float yOffset)
{
    glm::vec3 front = glm::cross(mUp, mRight);
    mPosition += front * yOffset;  // 透视相机的缩放其实就是相机沿front单位向量方法移动 front * yOffset 的距离
}
