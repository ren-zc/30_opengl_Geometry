#pragma once

#include "../../glframwork/core.h"
#include "camera.h"
#include <map>

class CameraControl
{
public:
	CameraControl();
	virtual ~CameraControl();

	// �̳�cameraControl�������п���ʵ���Լ����߼�
	virtual void onMouse(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float yOffset);

	// ÿһ֡��Ⱦ֮ǰ����, ÿһ֡���µ���Ϊ���Է�������
	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float sensitivity) { mSensitivity = sensitivity; }

protected:
	// ��갴��״̬
	bool mLeftMouseDown = false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	// ��ǰ���λ��
	float mCurrentX = 0.0f, mCurrentY = 0.0f;

	// ���ж�
	float mSensitivity = 0.2f;

	// ƽ�����ж�
	float mMoveSpeed = 0.1f;

	// ���������ж�
	float scaleSensitivity = 0.5f;

	// ��¼���̰��µ�״̬
	std::map<int, bool> mKeyMap;

	// ��¼��ǰ���Ƶ���һ�������
	Camera* mCamera = nullptr;
};

