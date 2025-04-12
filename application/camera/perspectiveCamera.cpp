#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far): mFovy(fovy), mAspect(aspect), mNear(near), mFar(far)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getProjectiveMatrix()
{
	// fovy: y�����Ž�, ���ȵ�λ, float����
    // aspect: ��ƽ��ĺ��ݰٷֱ�: ��/��, �ٴ�Ϊ800/600
    // near: �������ϵ�½�ƽ�����(����, ��Ȼλ��-z����)
    // far: �������ϵ��Զƽ�����

    // mFovy�ǽǶ�, Ӧ��ת��Ϊ����
    return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}

void PerspectiveCamera::scale(float yOffset)
{
    glm::vec3 front = glm::cross(mUp, mRight);
    mPosition += front * yOffset;  // ͸�������������ʵ���������front��λ���������ƶ� front * yOffset �ľ���
}
