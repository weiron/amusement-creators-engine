﻿
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "ace.Window_Imp_Win.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace {
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Window_Imp_Win::Unregist()
{
	if (!m_closed)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
		glfwTerminate();
		m_closed = true;
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Window_Imp* Window_Imp_Win::Create(int32_t width, int32_t height, const achar* title)
{
	if (!glfwInit())
	{
		return nullptr;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	auto titleUTF8 = ToUtf8String(title);

	auto window = glfwCreateWindow(width, height, titleUTF8.c_str(), NULL, NULL);
	if (window == nullptr)
	{
		glfwTerminate();
		return nullptr;
	}

	glfwSwapInterval(1);

	return new Window_Imp_Win( window, width, height );
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Window_Imp_Win::Window_Imp_Win(GLFWwindow* window, int32_t width, int32_t height)
	: m_window(window)
	, m_closed(false)
{
	m_size.X = width;
	m_size.Y = height;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Window_Imp_Win::~Window_Imp_Win()
{
	Unregist();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Window_Imp_Win::DoEvent()
{
	if (m_closed) return false;

	if (glfwWindowShouldClose(m_window))
	{
		Unregist();
		return false;
	}

	glfwPollEvents();
	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Window_Imp_Win::SetTitle( const achar* title )
{
	auto titleUTF8 = ToUtf8String(title);
	glfwSetWindowTitle(m_window, titleUTF8.c_str());
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Window_Imp_Win::Close()
{
	glfwSetWindowShouldClose(m_window, 1);
}


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}