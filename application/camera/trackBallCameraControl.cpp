#include "TrackBallCameraControl.h"

TrackBallCameraControl::TrackBallCameraControl()
{
}

TrackBallCameraControl::~TrackBallCameraControl()
{
}

void TrackBallCameraControl::onCursor(double xpos, double ypos)
{
	if (mLeftMouseDown)  // ������
	{
		// ��������ƶ�����
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;

		// pitch, yaw
		pitch(-deltaY);
		yaw(-deltaX);
	}
	else if (mMiddleMouseDown)  // ����м�ƽ��
	{
		// �����ƶ�����
		float deltaX = (xpos - mCurrentX) * mMoveSpeed;
		float deltaY = (ypos - mCurrentY) * mMoveSpeed;

		mCamera->mPosition += mCamera->mUp * deltaY;
		mCamera->mPosition -= mCamera->mRight * deltaX;
	}

	// ˢ����һ�����λ��
	mCurrentX = xpos;
	mCurrentY = ypos;
}

void TrackBallCameraControl::onScroll(float yOffset)
{
	// ����������
	mCamera->scale(yOffset * scaleSensitivity);
}

void TrackBallCameraControl::pitch(float angle)
{
	// ��mRight��ת
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);  // ��λ����, ����, ��(����)

	// Ӱ���������up��position����, ������ķ���������
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);  // '��ά����'����ά, ��Ҫ��0.0f, ��ά������ֵ����ά����, ֻȡǰ��ά
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);  // '����'ת��ά����, ��Ҫ��1.0f
}

void TrackBallCameraControl::yaw(float angle)
{
	// Χ����������ϵ��y����ת
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// Ӱ�쵽�������up right�Լ�position, ������ķ���������
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);  // ��ά����ת��ά����, ��Ҫ��0.0f, ��ά������ֵ����ά����, ֻȡǰ��ά
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);  // ����ת��ά����, ��Ҫ��1.0f
}
