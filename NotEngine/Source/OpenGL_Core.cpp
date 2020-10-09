#include "OpenGL_Core.h"
#include "OpenGL_Core.h"
#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool OpenGL::Core::Initialized = false;
int OpenGL::Enums::ColorBit = GL_COLOR_BUFFER_BIT;
int OpenGL::Enums::DepthBit = GL_DEPTH_BUFFER_BIT;

const char* OpenGL::Core::GetVendor()
{
	return (const char*)glGetString(GL_VENDOR);
}

const char* OpenGL::Core::GetRenderer()
{
	return (const char*)glGetString(GL_RENDERER);
}

const char* OpenGL::Core::GetVersion()
{
	return (const char*)glGetString(GL_VERSION);
}

void OpenGL::Core::LoadGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		NE_CORE_CRITICAL("OpenGL failed to Load.");
		bool OpenGL_Initialized = false;
		assert(OpenGL_Initialized == true);
	}

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Driver Info ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Vendor\t\t:\t" << glGetString(GL_VENDOR) << "\n";
	std::cout << "Renderer\t:\t" << glGetString(GL_RENDERER) << "\n";
	std::cout << "OpenGL Version\t:\t" << glGetString(GL_VERSION) << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

	OpenGL::Core::Initialized = true;
}

void OpenGL::Core::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void OpenGL::Core::ClearBufferBits(int bits)
{
	glClear(bits);
}

void OpenGL::Core::EnableWireframeMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGL::Core::EnableSoildMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGL::Core::SetBlending(bool ToogleBlend)
{
	if (ToogleBlend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void OpenGL::Core::SetDepthTest(bool ToogleDepthTest)
{
	ToogleDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void OpenGL::Core::SetViewportSize(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
}
