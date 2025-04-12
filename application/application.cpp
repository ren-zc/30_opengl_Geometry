#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application()
{
}

Application::~Application()
{
}

Application* Application::mInstance = nullptr;  // ��ʼ����̬˽�е�ʵ����Ա����

Application* Application::getInstance()
{
	// ���instanceΪ��, ���ʼ��instance
	// ����instance
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

	// 1. ��ʼ��glfw��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2. �����������
	mWindow = glfwCreateWindow(mWidth, mHeight, "Learn Opengl", NULL, NULL); // 2.1
	if (mWindow == NULL)
	{
		return false;
	}

	glfwMakeContextCurrent(mWindow); // 2.1 ���õ�ǰ����

	// 7. ����glad����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to load GLAD" << std::endl; // �������ʧ��
		return false;
	}

	// ���ô��ڱ仯�ص�
	glfwSetFramebufferSizeCallback(mWindow, frambufferSizeChangeCallback);

	// this�ǵ�ǰȫ��Ψһ��Application����
	//glfwSetWindowUserPointer(mWindow, this); // ����frambufferSizeChangeCallback�����glfwGetWindowUserPointer

	// ���ü�����Ϣ�ص�
	glfwSetKeyCallback(mWindow, keyboardEventHandler);

	// ��갴ť��λ�ûص�
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
	// ���ղ��ַ�������Ϣ
	// �����Ϣ�����Ƿ�Ҫ��������\���̵���Ϣ
	// ����еĻ��ͽ���Ϣ��������, ����ն���
	glfwPollEvents();

	// 12. �л�˫����
	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destroy()
{
	// 4. �Ƴ�����ǰ���������
	glfwTerminate();
}

void Application::frambufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	//std::cout << "frambufferSizeChangeCallback" << std::endl;
	//if (Application::mInstance->mResizeCallback != nullptr)
	//{
	//	Application::mInstance->mResizeCallback(width, height);
	//}

	// �����ŵķ���
	//Application* self = (Application*)glfwGetWindowUserPointer(window); 
	if (app->mResizeCallback != nullptr)  // app��self����
	{
		app->mResizeCallback(width, height);
	}
}

void Application::keyboardEventHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "keyboradCallback" << std::endl;
	if (app->mKeyboardCallback != nullptr)  // �˴�Ҳ����ʹ��self
	{
		app->mKeyboardCallback(key, action, mods);
	}
}

void Application::mouseEventHandler(GLFWwindow* window, int button, int action, int mods)
{
	//std::cout << "����¼�: " << button << "," << action << std::endl;
	if (app->mMouseCallback != nullptr)
	{
		app->mMouseCallback(button, action, mods);
	}
}

void Application::cursorEventHandler(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "���λ���¼�: " << xpos << "," << ypos << std::endl;
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
