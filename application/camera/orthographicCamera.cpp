#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float l, float r, float t, float b, float n, float f):
	mLeft(l), mRight(r), mTop(t), mBottom(b), mNear(n), mFar(f){}

OrthographicCamera::~OrthographicCamera()
{
}

glm::mat4 OrthographicCamera::getProjectiveMatrix()
{
	// -x, x, -y, y, near, far
	float scaleValue = glm::pow(2.0, mScale);
	return glm::ortho(mLeft * scaleValue, mRight * scaleValue, mBottom * scaleValue, mTop * scaleValue, mNear, mFar);
}

void OrthographicCamera::scale(float yOffset)
{
	mScale += yOffset;
}
