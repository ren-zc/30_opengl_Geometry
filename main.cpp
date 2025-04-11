#include <iostream>
#include "glframwork/core.h"
#include "wrapper/checkError.h"
#include "application/application.h"
#include "glframwork/shader.h"
#include "glframwork/texture.h"
#include "application/camera/perspectiveCamera.h"
#include "application/camera/orthographicCamera.h"
#include "application/camera/trackBallCameraControl.h"
#include "application/camera/gameCameraControl.h"
#include "glframwork/geometry.h"

/*
* 目标30
*/

// 声明全局变量
Texture* texture=nullptr;
Shader* shader = nullptr;
glm::mat4 transform(1.0f);

PerspectiveCamera* camera = nullptr;  // 透视相机矩阵
//OrthographicCamera* camera = nullptr;  // 透视相机矩阵
GameCameraControl* gameCameraControl = nullptr;  // 相机控制器
TrackBallCameraControl* tackBallCameraControl = nullptr;  // 相机控制器

// *** 所有事件必须在main重新包装一次, 因为app的事件回调接口不能直接对接cameraControl事件处理函数 ***

// 鼠标滚轮事件
void onScroll(double yOffset) {
	gameCameraControl->onScroll(yOffset);
	tackBallCameraControl->onScroll(yOffset);
}

// onMouse
void onMouseButton(int button, int action, int mods) {
	//std::cout<< "鼠标点击: " << button << std::endl;
	double x, y;
	app->getMousePosition(&x, &y);
	gameCameraControl->onMouse(button, action, x, y);
	tackBallCameraControl->onMouse(button, action, x, y);
}

// OnCursor
void onCursor(double xpos, double ypos) {
	//std::cout << "鼠标移动: " << xpos << "," << ypos << std::endl;
	gameCameraControl->onCursor(xpos, ypos);
	tackBallCameraControl->onCursor(xpos, ypos);
}

// 用于Application
void onSizeChange(int width, int height) {
	//std::cout << "onSizeChange" << std::endl;
	glViewport(0, 0, width, height);
}

// onKey
void handleKeyEvent(int key, int action, int mods) {
	gameCameraControl->onKey(key, action, mods);
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTransform() {
	// 先沿x轴平移2
	auto tranlate1 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0f, 0.0f));
	//transform = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0f, 0.0f));

	// 在放大3倍
	auto scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f));

	transform = scale1 * tranlate1;
}

void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

// 渲染程序
void render(GLuint vao, unsigned int indicesCount) {
	// 清理画布
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	// 开始shader程序
	shader->begin();
	shader->setUniform1i("Sampler", 0);
	shader->setMetrix4("transform", transform);
	shader->setMetrix4("viewMatrix", camera->getViewMatrix());
	shader->setMetrix4("projectionMatrix", camera->getProjectiveMatrix());

	// 绑定vao
	glBindVertexArray(vao);

	// glDrawElement
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0); // 不偏移
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 不偏移
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(int)));  // 偏移3个顶点索引

	glBindVertexArray(0);
	shader->end();
}

void prepareTexture() {
	texture = new Texture("assets/textures/earth.jpg", 0);
}

void  prepareCamera() {
	//float size = 8.0;
	//camera = new OrthographicCamera(-size, size, size, -size, size, -size);
	camera = new PerspectiveCamera(
		60.0f,
		(float)app->getWidth() / (float)app->getHeight(),
		0.1f,
		1000.0f
	);

	gameCameraControl = new GameCameraControl();
	gameCameraControl->setCamera(camera);
	gameCameraControl->setSensitivity(0.4f);

	tackBallCameraControl = new TrackBallCameraControl();
	tackBallCameraControl->setCamera(camera);
	tackBallCameraControl->setSensitivity(0.4f);
}

//void prepareOrtho() {
//	// -x, x, -y, y, near, far
//	projectionMatrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
//}

int main() {
	if (!app->init(800, 600))
	{
		return -1;
	}

	app->setResizeCallback(onSizeChange);
	app->setKeyboardCallback(handleKeyEvent);
	app->setMouseCallback(onMouseButton);
	app->setCursorCallback(onCursor);
	app->setScrollCallback(onScroll);

	// 8. 设置视口大小
	GL_CALL(glViewport(0, 0, 800, 600));
	// 9. 设置清理屏幕用的颜色
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	prepareState();
	prepareShader();
	prepareTexture();
	prepareCamera();
	//prepareOrtho();
	//preparePerspective();
	//prepareTransform();

	//Geometry* geometry = Geometry::createBox(6.0f);
	Geometry* geometry = Geometry::createSphere(3.0f);

	while(app->update()){
		gameCameraControl->update();
		render(geometry->getVao(), geometry->getIndicesCount());
	}
	
	// 4. 推出程序前做相关清理
	app->destroy();
	delete(texture);

	return 0;
}
