#include "cameraControl.h"
#include "cameraControl.h"
#include <iostream>

CameraControl::CameraControl()
{
}

CameraControl::~CameraControl()
{
}

void CameraControl::onMouse(int button, int action, double xpos, double ypos)
{
	//std::cout << "onMouse" << std::endl;
	// 判断当前的按钮是否按下
	bool pressed = action == GLFW_PRESS ? true : false;

	// 若已按下, 记录当前按下的位置
	if (pressed)
	{
		mCurrentX = xpos;
		mCurrentY = ypos;
	}

	// 根据按下数据按钮的不同, 更改案件状态
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMouseDown = pressed;
		break;
	}
}

void CameraControl::onCursor(double xpos, double ypos)
{
	//std::cout << "onCursor" << std::endl;
}

void CameraControl::onKey(int key, int action, int mods)
{
	// 过滤repeat
	if (action == GLFW_REPEAT)
	{
		return;
	}

	//std::cout << "onKey" << std::endl;
	// 检测按下还是抬起, 给到一个变量, 按下: true, 抬起: false
	bool pressed = action == GLFW_PRESS ? true : false;

	// 记录在map中
	mKeyMap[key] = pressed;
}

void CameraControl::onScroll(float yOffset)
{
}

void CameraControl::update()
{
	//std::cout << "camera control update" << std::endl;
}

