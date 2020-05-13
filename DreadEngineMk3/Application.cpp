#include "Application.h"
#include <iostream>

Application::Application(int width, int height, const char* name)
{
	Create(width, height, name);
}

Application::~Application()
{
	glfwDestroyWindow(m_window);
	glfwTerminate(); 
}

int Application::Create(int width, int height, const char* name)
{
	//Checking if glfw failed to initialise
	if (glfwInit() == false)
	{
		std::cout << "Failed to initiate GLFW" << std::endl; 
		return -1;
	}

	//Creating the window 
	m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	//Checking if window was made successfully 
	if (m_window == nullptr)
	{
		glfwTerminate(); 
		std::cout << "Failed to create window" << std::endl;
		return -2; 
	}
	
	//This must be done before loading functions
	//	Don't know why 
	glfwMakeContextCurrent(m_window);
	

	//Remapping of OpenGL functions and checking success
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		std::cout << "Failed to remap OpneGl function calls" << std::endl; 
		return -3; 
	}

	//Checking which version of OpenGl we are running 
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	std::cout << "GL: " << major << "." << minor << std::endl;
	return 0; 
}