#include "TrackBallCameraControl.h"

TrackBallCameraControl::TrackBallCameraControl()
{
}

TrackBallCameraControl::~TrackBallCameraControl()
{
}

void TrackBallCameraControl::onCursor(double xpos, double ypos)
{
	if (mLeftMouseDown)  // 鼠标左键
	{
		// 计算鼠标移动距离
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;

		// pitch, yaw
		pitch(-deltaY);
		yaw(-deltaX);
	}
	else if (mMiddleMouseDown)  // 鼠标中间平移
	{
		// 计算移动距离
		float deltaX = (xpos - mCurrentX) * mMoveSpeed;
		float deltaY = (ypos - mCurrentY) * mMoveSpeed;

		mCamera->mPosition += mCamera->mUp * deltaY;
		mCamera->mPosition -= mCamera->mRight * deltaX;
	}

	// 刷新上一个鼠标位置
	mCurrentX = xpos;
	mCurrentY = ypos;
}

void TrackBallCameraControl::onScroll(float yOffset)
{
	// 鼠标滚轮缩放
	mCamera->scale(yOffset * scaleSensitivity);
}

void TrackBallCameraControl::pitch(float angle)
{
	// 绕mRight旋转
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);  // 单位矩阵, 弧度, 轴(向量)

	// 影响摄像机的up和position向量, 相机看的方向是球心
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);  // '三维向量'升四维, 需要补0.0f, 四维向量赋值给三维变量, 只取前三维
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);  // '坐标'转四维向量, 需要补1.0f
}

void TrackBallCameraControl::yaw(float angle)
{
	// 围绕世界坐标系的y轴旋转
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// 影响到了相机的up right以及position, 相机看的方向是球心
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);  // 三维向量转四维向量, 需要补0.0f, 四维向量赋值给三维变量, 只取前三维
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);  // 坐标转四维向量, 需要补1.0f
}
