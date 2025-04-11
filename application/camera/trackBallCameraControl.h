#pragma once
#include "cameraControl.h"

class TrackBallCameraControl: public CameraControl
{
public:
	TrackBallCameraControl();
	~TrackBallCameraControl();

	void onCursor(double xpos, double ypos) override;
	void onScroll(float yOffset) override;

private:
	void pitch(float angle);  // ����ת��, ��mRight
	void yaw(float angle);  // γ��ת��, ������y��
};
