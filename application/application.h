#pragma once
#include <iostream>
//#include <GLFW/glfw3.h>


/*
* 全局唯一单例应用, 表示当前应用程序本身
* 声明周期 init -> 每一帧update -> destroy
* 
* 1. 单实例
* 2. 成员变量+成员函数
*	2.1 成员函数init(初始化)
*	2.2 成员函数update(每一帧执行)
*	2.3 成员函数destroy(结尾执行)
* 3. 窗口变化callback
*	3.1 声明ResizeCallback类型
*	3.2 声明ResizeCallback类型的私有变量(默认nullptr)
*	3.3 声明并定义公开的设置ResizeCallback类型变量的方法setResizeCallback
*	3.4 声明并定义glfwSetFramebufferSizeCallback直接调用的静态成员方法: frambufferSizeChangeCallback(在对象内必须是静态的)
*	3.5 frambufferSizeChangeCallback方法中调用ResizeCallback类型变量mResizeCallback(若不为空指针)
*	3.6 在Application实例init中设置回调:glfwSetFramebufferSizeCallback(mWindow, frambufferSizeChangeCallback);
*	3.7 用户定义callback函数: onSizeChange, 并赋值给ResizeCallback类型变量mResizeCallback
* 4. 键盘消息事件callback
*	4.1 用于glfw直接调用的静态成员函数:keyboardCallback
*	4.2 init中glfw调用keyboardEventHandler
*	4.3 定义键盘消息回调函数类型KeyboardCallback
*	4.4 定义KeyboardCallback类型的私有变量mKeyboardCallback(并初始化为nullptr)
*	4.5 添加设置mKeyboardCallback的方法setKeyboardCallback
*	4.6 在keyboardEventHandler中调用mKeyboardCallback指向的方法
*	4.7 用户自定义符合KeyboardCallback签名的函数
*	4.8 把函数赋值给mKeyboardCallback
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

	void getMousePosition(double* x, double* y);  // 获取鼠标当前位置的函数

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
	static Application* mInstance; // 全局唯一静态变量实例

	// glfwSetFramebufferSizeCallback要么是个静态(static)成员, 要么是个独立的函数(即: 非对象内的成员函数)
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

	Application(); // 构造方法放在private部分, 防止被外部调用
};
