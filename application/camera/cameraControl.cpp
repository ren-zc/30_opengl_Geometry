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
	// �жϵ�ǰ�İ�ť�Ƿ���
	bool pressed = action == GLFW_PRESS ? true : false;

	// ���Ѱ���, ��¼��ǰ���µ�λ��
	if (pressed)
	{
		mCurrentX = xpos;
		mCurrentY = ypos;
	}

	// ���ݰ������ݰ�ť�Ĳ�ͬ, ���İ���״̬
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
	// ����repeat
	if (action == GLFW_REPEAT)
	{
		return;
	}

	//std::cout << "onKey" << std::endl;
	// ��ⰴ�»���̧��, ����һ������, ����: true, ̧��: false
	bool pressed = action == GLFW_PRESS ? true : false;

	// ��¼��map��
	mKeyMap[key] = pressed;
}

void CameraControl::onScroll(float yOffset)
{
}

void CameraControl::update()
{
	//std::cout << "camera control update" << std::endl;
}

