#pragma once

#include "../../glframwork/core.h"
#include "camera.h"
#include <map>

class CameraControl
{
public:
	CameraControl();
	virtual ~CameraControl();

	// 继承cameraControl的子类有可能实现自己的逻辑
	virtual void onMouse(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float yOffset);

	// 每一帧渲染之前调用, 每一帧更新的行为可以放在这里
	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float sensitivity) { mSensitivity = sensitivity; }

protected:
	// 鼠标按键状态
	bool mLeftMouseDown = false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	// 当前鼠标位置
	float mCurrentX = 0.0f, mCurrentY = 0.0f;

	// 敏感度
	float mSensitivity = 0.2f;

	// 平移敏感度
	float mMoveSpeed = 0.1f;

	// 鼠标滚轮敏感度
	float scaleSensitivity = 0.5f;

	// 记录键盘按下的状态
	std::map<int, bool> mKeyMap;

	// 记录当前控制的哪一个摄像机
	Camera* mCamera = nullptr;
};

