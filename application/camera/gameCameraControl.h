#pragma once
#include "cameraControl.h"

class GameCameraControl: public CameraControl
{
public:
	GameCameraControl();
	~GameCameraControl();

	// ����������Ϸ���Ƶ�����ƶ�ʱ���п���
	void onCursor(double xpos, double ypos) override;

	// ���̲�����updateʱ����
	void update() override;

private:

	void pitch(float angle);  // ���������mRight������ת��
	void yaw(float angle);  // ������¼�y��ת��, �����ƶ�λ��

	//float mSensitivity = 0.1f;  // pitch������

	float mBaseDeltaY{ 0.0f };  // �ۼӽǶ�, ��ʾ����ת���ķ�Χ -90��~90��
	float mSpeed{ 0.5f };  // ����ƶ��ٶ�

};
