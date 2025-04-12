#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application()
{
}

Application::~Application()
{
}

Application* Application::mInstance = nullptr;  // 初始化静态私有单实例成员变量

Application* Application::getInstance()
{
	// 如果instance为空, 则初始化instance
	// 返回instance
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}
	return mInstance;
}

void Application::getMousePosition(double* x, double* y)
{
	glfwGetCursorPos(mWindow, x, y);
}

bool Application::init(const int& width, const int& height)
{
	mWidth = width;
	mHeight = height;

	// 1. 初始化glfw基本环境
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2. 创建窗体对象
	mWindow = glfwCreateWindow(mWidth, mHeight, "Learn Opengl", NULL, NULL); // 2.1
	if (mWindow == NULL)
	{
		return false;
	}

	glfwMakeContextCurrent(mWindow); // 2.1 设置当前窗口

	// 7. 加载glad函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to load GLAD" << std::endl; // 如果加载失败
		return false;
	}

	// 设置窗口变化回调
	glfwSetFramebufferSizeCallback(mWindow, frambufferSizeChangeCallback);

	// this是当前全局唯一的Application对象
	//glfwSetWindowUserPointer(mWindow, this); // 下面frambufferSizeChangeCallback会调用glfwGetWindowUserPointer

	// 设置键盘消息回调
	glfwSetKeyCallback(mWindow, keyboardEventHandler);

	// 鼠标按钮和位置回调
	glfwSetMouseButtonCallback(mWindow, mouseEventHandler);
	glfwSetCursorPosCallback(mWindow, cursorEventHandler);
	glfwSetScrollCallback(mWindow, scrollEventHandler);

	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}
	// 接收并分发窗体消息
	// 检查消息队列是否要处理的鼠标\键盘等消息
	// 如果有的话就将消息批量处理, 并清空队列
	glfwPollEvents();

	// 12. 切换双缓存
	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destroy()
{
	// 4. 推出程序前做相关清理
	glfwTerminate();
}

void Application::frambufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	//std::cout << "frambufferSizeChangeCallback" << std::endl;
	//if (Application::mInstance->mResizeCallback != nullptr)
	//{
	//	Application::mInstance->mResizeCallback(width, height);
	//}

	// 更优雅的方法
	//Application* self = (Application*)glfwGetWindowUserPointer(window); 
	if (app->mResizeCallback != nullptr)  // app或self都行
	{
		app->mResizeCallback(width, height);
	}
}

void Application::keyboardEventHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "keyboradCallback" << std::endl;
	if (app->mKeyboardCallback != nullptr)  // 此处也可以使用self
	{
		app->mKeyboardCallback(key, action, mods);
	}
}

void Application::mouseEventHandler(GLFWwindow* window, int button, int action, int mods)
{
	//std::cout << "鼠标事件: " << button << "," << action << std::endl;
	if (app->mMouseCallback != nullptr)
	{
		app->mMouseCallback(button, action, mods);
	}
}

void Application::cursorEventHandler(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "鼠标位置事件: " << xpos << "," << ypos << std::endl;
	if (app->mCursorCallback != nullptr)
	{
		app->mCursorCallback(xpos, ypos);
	}
}

void Application::scrollEventHandler(GLFWwindow* window, double xOffset, double yOffset)
{
	if (app->mScrollCallback!=nullptr)
	{
		//float yOffsetF = static_cast<float>(yOffset);
		app->mScrollCallback(yOffset);
	}
}
