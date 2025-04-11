#include "gameCameraControl.h"

GameCameraControl::GameCameraControl()
{
}

GameCameraControl::~GameCameraControl()
{
}

void GameCameraControl::onCursor(double xpos, double ypos)
{
	float deltaX = xpos - mCurrentX;
	float deltaY = ypos - mCurrentY;

	if (mRightMouseDown)  // ����Ҽ�
	{
		pitch(-deltaY * mSensitivity);
		yaw(-deltaX * mSensitivity);
	}

	mCurrentX = xpos;
	mCurrentY = ypos;
}

// ������ת
void GameCameraControl::pitch(float angle)
{
	mBaseDeltaY += angle;  // �����ȼ�
	if (mBaseDeltaY > 89.0f || mBaseDeltaY < -89.0f)
	{
		mBaseDeltaY -= angle;  // �����ȼ��ټ�, ����ǶȾͿ����ڱ߽�����
		return;
	}

	// ������ת����
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);  // ���������mRightת��, up�����任, ��������
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
}

// ������y��������ת
void GameCameraControl::yaw(float angle)
{
	// ������ת����
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// �����up��right�����������仯
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}

void GameCameraControl::update()
{
	// W A S D�ƶ�
	glm::vec3 front = glm::cross(mCamera->mUp, mCamera->mRight);
	glm::vec3 right = mCamera->mRight;

	glm::vec3 direction{ 0.0f, 0.0f, 0.0f };

	if (mKeyMap[GLFW_KEY_W])  // w
	{
		direction += front;
	}
	if (mKeyMap[GLFW_KEY_A])  // a
	{
		direction -= right;
	}
	if (mKeyMap[GLFW_KEY_S])  // s
	{
		direction -= front;
	}
	if (mKeyMap[GLFW_KEY_D])  // d
	{
		direction += right;
	}

	// �ƶ�, ����ʱλ�÷����˱仯
	// ֻ��directionģ��Ϊ0ʱ, �Ż��ƶ�, �Ҳ��ܹ�һ��
	if (glm::length(direction)!=0)
	{
		direction = glm::normalize(direction);  // !!!��Ҫ: һ��Ҫ���й�һ��, ǰ����������ģ��Ϊ0;
		mCamera->mPosition += direction * mSpeed;
	}

}
