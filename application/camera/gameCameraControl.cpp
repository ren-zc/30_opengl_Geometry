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

	if (mRightMouseDown)  // 鼠标右键
	{
		pitch(-deltaY * mSensitivity);
		yaw(-deltaX * mSensitivity);
	}

	mCurrentX = xpos;
	mCurrentY = ypos;
}

// 上下旋转
void GameCameraControl::pitch(float angle)
{
	mBaseDeltaY += angle;  // 必须先加
	if (mBaseDeltaY > 89.0f || mBaseDeltaY < -89.0f)
	{
		mBaseDeltaY -= angle;  // 必须先加再减, 否则角度就卡死在边界外了
		return;
	}

	// 计算旋转矩阵
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);  // 相机绕自身mRight转动, up向量变换, 其他不变
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
}

// 绕世界y轴左右旋转
void GameCameraControl::yaw(float angle)
{
	// 计算旋转矩阵
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// 相机的up和right向量都发生变化
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}

void GameCameraControl::update()
{
	// W A S D移动
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

	// 移动, 仅仅时位置发生了变化
	// 只有direction模不为0时, 才会移动, 且才能归一化
	if (glm::length(direction)!=0)
	{
		direction = glm::normalize(direction);  // !!!重要: 一定要进行归一化, 前提是向量的模不为0;
		mCamera->mPosition += direction * mSpeed;
	}

}
