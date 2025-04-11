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
	void pitch(float angle);  // 经度转动, 绕mRight
	void yaw(float angle);  // 纬度转动, 绕世界y轴
};
