#pragma once
#include <iostream>
//#include <GLFW/glfw3.h>


/*
* ȫ��Ψһ����Ӧ��, ��ʾ��ǰӦ�ó�����
* �������� init -> ÿһ֡update -> destroy
* 
* 1. ��ʵ��
* 2. ��Ա����+��Ա����
*	2.1 ��Ա����init(��ʼ��)
*	2.2 ��Ա����update(ÿһִ֡��)
*	2.3 ��Ա����destroy(��βִ��)
* 3. ���ڱ仯callback
*	3.1 ����ResizeCallback����
*	3.2 ����ResizeCallback���͵�˽�б���(Ĭ��nullptr)
*	3.3 ���������幫��������ResizeCallback���ͱ����ķ���setResizeCallback
*	3.4 ����������glfwSetFramebufferSizeCallbackֱ�ӵ��õľ�̬��Ա����: frambufferSizeChangeCallback(�ڶ����ڱ����Ǿ�̬��)
*	3.5 frambufferSizeChangeCallback�����е���ResizeCallback���ͱ���mResizeCallback(����Ϊ��ָ��)
*	3.6 ��Applicationʵ��init�����ûص�:glfwSetFramebufferSizeCallback(mWindow, frambufferSizeChangeCallback);
*	3.7 �û�����callback����: onSizeChange, ����ֵ��ResizeCallback���ͱ���mResizeCallback
* 4. ������Ϣ�¼�callback
*	4.1 ����glfwֱ�ӵ��õľ�̬��Ա����:keyboardCallback
*	4.2 init��glfw����keyboardEventHandler
*	4.3 ���������Ϣ�ص���������KeyboardCallback
*	4.4 ����KeyboardCallback���͵�˽�б���mKeyboardCallback(����ʼ��Ϊnullptr)
*	4.5 �������mKeyboardCallback�ķ���setKeyboardCallback
*	4.6 ��keyboardEventHandler�е���mKeyboardCallbackָ��ķ���
*	4.7 �û��Զ������KeyboardCallbackǩ���ĺ���
*	4.8 �Ѻ�����ֵ��mKeyboardCallback
*/

#define app Application::getInstance()

struct GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyboardCallback = void(*)(int key, int action, int mods);
using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);
using ScrollCallback = void(*)(double yOffset);

class Application
{
public:
	~Application();
	static Application* getInstance();

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }

	void getMousePosition(double* x, double* y);  // ��ȡ��굱ǰλ�õĺ���

	/*void test() {
		std::cout << "Application test" << std::endl;
	}*/

	bool init(const int& width=800, const int& height=600);
	bool update();
	void destroy();

	void setResizeCallback(ResizeCallback func) { mResizeCallback = func; }
	void setKeyboardCallback(KeyboardCallback func) { mKeyboardCallback = func; }
	void setMouseCallback(MouseCallback func) { mMouseCallback = func; }
	void setCursorCallback(CursorCallback func) { mCursorCallback = func; }
	void setScrollCallback(ScrollCallback func) { mScrollCallback = func; }

private:
	static Application* mInstance; // ȫ��Ψһ��̬����ʵ��

	// glfwSetFramebufferSizeCallbackҪô�Ǹ���̬(static)��Ա, Ҫô�Ǹ������ĺ���(��: �Ƕ����ڵĳ�Ա����)
	static void frambufferSizeChangeCallback(GLFWwindow* window, int with, int height);
	static void keyboardEventHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseEventHandler(GLFWwindow* window, int button, int action, int mods);
	static void cursorEventHandler(GLFWwindow* window, double xpos, double ypos);
	static void scrollEventHandler(GLFWwindow* window, double xOffset, double yOffset);

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };
	ResizeCallback mResizeCallback{ nullptr };
	KeyboardCallback mKeyboardCallback{ nullptr };
	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };

	Application(); // ���췽������private����, ��ֹ���ⲿ����
};
