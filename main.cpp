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
* Ŀ��30
*/

// ����ȫ�ֱ���
Texture* texture=nullptr;
Shader* shader = nullptr;
glm::mat4 transform(1.0f);

PerspectiveCamera* camera = nullptr;  // ͸���������
//OrthographicCamera* camera = nullptr;  // ͸���������
GameCameraControl* gameCameraControl = nullptr;  // ���������
TrackBallCameraControl* tackBallCameraControl = nullptr;  // ���������

// *** �����¼�������main���°�װһ��, ��Ϊapp���¼��ص��ӿڲ���ֱ�ӶԽ�cameraControl�¼������� ***

// �������¼�
void onScroll(double yOffset) {
	gameCameraControl->onScroll(yOffset);
	tackBallCameraControl->onScroll(yOffset);
}

// onMouse
void onMouseButton(int button, int action, int mods) {
	//std::cout<< "�����: " << button << std::endl;
	double x, y;
	app->getMousePosition(&x, &y);
	gameCameraControl->onMouse(button, action, x, y);
	tackBallCameraControl->onMouse(button, action, x, y);
}

// OnCursor
void onCursor(double xpos, double ypos) {
	//std::cout << "����ƶ�: " << xpos << "," << ypos << std::endl;
	gameCameraControl->onCursor(xpos, ypos);
	tackBallCameraControl->onCursor(xpos, ypos);
}

// ����Application
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
	// ����x��ƽ��2
	auto tranlate1 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0f, 0.0f));
	//transform = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0f, 0.0f));

	// �ڷŴ�3��
	auto scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f));

	transform = scale1 * tranlate1;
}

void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

// ��Ⱦ����
void render(GLuint vao, unsigned int indicesCount) {
	// ������
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	// ��ʼshader����
	shader->begin();
	shader->setUniform1i("Sampler", 0);
	shader->setMetrix4("transform", transform);
	shader->setMetrix4("viewMatrix", camera->getViewMatrix());
	shader->setMetrix4("projectionMatrix", camera->getProjectiveMatrix());

	// ��vao
	glBindVertexArray(vao);

	// glDrawElement
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0); // ��ƫ��
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ��ƫ��
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(int)));  // ƫ��3����������

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

	// 8. �����ӿڴ�С
	GL_CALL(glViewport(0, 0, 800, 600));
	// 9. ����������Ļ�õ���ɫ
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
	
	// 4. �Ƴ�����ǰ���������
	app->destroy();
	delete(texture);

	return 0;
}
