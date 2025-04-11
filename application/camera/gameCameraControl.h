#pragma once
#include "cameraControl.h"

class GameCameraControl: public CameraControl
{
public:
	GameCameraControl();
	~GameCameraControl();

	// 玩家相机在游戏控制的鼠标移动时进行控制
	void onCursor(double xpos, double ypos) override;

	// 键盘操作在update时控制
	void update() override;

private:

	void pitch(float angle);  // 相机绕自身mRight轴上下转动
	void yaw(float angle);  // 相机绕事件y轴转动, 单不移动位置

	//float mSensitivity = 0.1f;  // pitch灵敏度

	float mBaseDeltaY{ 0.0f };  // 累加角度, 显示上下转动的范围 -90°~90°
	float mSpeed{ 0.5f };  // 玩家移动速度

};
