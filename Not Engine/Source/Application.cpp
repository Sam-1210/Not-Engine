#include <string>
#include "Application.h"
#include "Engine.h"
#include "Log.h"
#include <iostream>

int Application::InstanceCounter = 0;
Application* Application::ActiveApplication = nullptr;

Application::Application()
{
	Initialized = false;
	Resizable = true;
	VSync = false;
	Wireframe = false;
	ID = InstanceCounter++;
	engine = new Engine(ID, this);
	GL_Version = glm::vec2(3, 3);
	WindowMode = WrapperEnum::Mode_Windowed;
	WindowPosition = glm::vec2(0, 50);
	WindowSize = glm::vec2(800, 600);
	ViewportSize = WindowSize;
	WindowTitle = "Application";
	window = nullptr;
	Logger::Init();
	std::cout << "\t\t\t\t\t:::::::: NotEngine ::::::::\n\n\n\n";
}

Application::Application(const std::string& WinTitle, const glm::vec2& _WinSize, const glm::vec2 WinPos,
	const glm::vec2& _GL_Version, const bool& Logging, const bool& _Resizable, 
	const bool& _VerticalSync, const WrapperEnum& WinMode, const bool& _Wireframe)
{
	Initialized = false;
	Resizable = _Resizable;
	VSync = _VerticalSync;
	Wireframe = _Wireframe;
	ID = InstanceCounter++;
	engine = new Engine(ID, this);
	GL_Version = _GL_Version;
	WindowMode = WinMode;
	WindowPosition = WinPos;
	WindowSize = _WinSize;
	ViewportSize = WindowSize;
	WindowTitle = WinTitle;
	window = nullptr;
	Logger::Init();
	std::cout << "\t\t\t\t\t:::::::: NotEngine ::::::::\n\n\n\n";
}

Application::~Application()
{
	--InstanceCounter;
	NE_CORE_INFO("Application Deleted, Instance ID : {0}", ID);
	glfwTerminate();
}

MyStatus Application::Init()
{
	if (this->Initialized)
		return MyStatus::Already_Initialized;

	if (!glfwInit())
	{
		NE_CORE_CRITICAL("GLFW failed to Initialize");
		NE_CORE_ERROR("Application Initialization Failed");
		return MyStatus::GLFW_Init_Error;
	}

	window = glfwCreateWindow((int)WindowSize.x, (int)WindowSize.y, WindowTitle.c_str(), nullptr, nullptr);
	if (!window)
	{
		NE_CORE_CRITICAL("GLFW failed to Create Window");
		NE_CORE_ERROR("Application Initialization Failed");
		return MyStatus::Window_Creation_Error;
	}

	SetContextCurrent(this);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)GL_Version.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)GL_Version.y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	SetResizable(Resizable);
	SetVSync(VSync);
	SetWireFrameMode(Wireframe);
	SetWindowMode(WindowMode);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		NE_CORE_CRITICAL("GLAD failed to Initialize");
		NE_CORE_ERROR("Application Initialization Failed");
		return MyStatus::GLAD_Init_Error;
	}
	EnableTransparency();

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Driver Info ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Vendor\t\t:\t" << glGetString(GL_VENDOR) << "\n";
	std::cout << "Renderer\t:\t" << glGetString(GL_RENDERER) << "\n";
	std::cout << "OpenGL Version\t:\t" << glGetString(GL_VERSION) << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	NE_CORE_INFO("Window \'" + WindowTitle + "\' Created Successfully");
	NE_CORE_INFO("Application Initialized Successfully, Instance ID {0}", ID);

	this->Initialized = true;
	return MyStatus::Init_Success;
}

void Application::Exit()
{
	glfwSetWindowShouldClose(window, true);
}

void Application::SetContextCurrent(Application* App)
{
	ActiveApplication = App;
	glfwMakeContextCurrent(App->GetWindowObject());
}

void Application::ResizeWindowHandler(GLFWwindow* Window, int w, int h)
{
	ActiveApplication->SetWindowSize(glm::vec2(w, h));
	ActiveApplication->SetViewportSize(glm::vec2(w, h));
	glViewport(0, 0, w, h);
}

bool Application::GetVSync() const
{
	return VSync;
}

bool Application::IsResizable() const
{
	return Resizable;
}

bool Application::IsWireframe() const
{
	return Wireframe;
}

bool Application::WindowIsNotClosed() const
{
	bool status = glfwWindowShouldClose(window);
	if (status)
		NE_CORE_WARN("Window " + WindowTitle +" Closed");
	return !status;
}

Engine* Application::GetEngine() const
{
	return engine;
}

glm::vec2 Application::GetGL_Version() const
{
	return GL_Version;
}

glm::vec2 Application::GetWindowSize() const
{
	return WindowSize;
}

glm::vec2 Application::GetViewportSize() const
{
	return ViewportSize;
}

WrapperEnum Application::GetWindowMode() const
{
	return WindowMode;
}

std::string Application::GetWindowTitle() const
{
	return WindowTitle;
}

GLFWwindow* Application::GetWindowObject() const
{
	return window;
}

void Application::EnableTransparency()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::DisableTransparency()
{
	glDisable(GL_BLEND);
}

void Application::SetDepthTest(const bool& DepthTest)
{
	if (DepthTest)
	{
		glEnable(GL_DEPTH_TEST);
		NE_CORE_INFO("DepthTest Enabled");
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		NE_CORE_WARN("DepthTest Disabled");
	}
}

void Application::SetResizable(const bool& Resizable)
{
	this->Resizable = Resizable;
	glfwWindowHint(GLFW_RESIZABLE, Resizable);
	if (Resizable)
		glfwSetFramebufferSizeCallback(window, ResizeWindowHandler);
	else
		glfwSetFramebufferSizeCallback(window, nullptr);
}

void Application::SetVSync(const bool& VerticalSync)
{
	VSync = VerticalSync;
	VSync ? glfwSwapInterval(1) : glfwSwapInterval(0);
}

void Application::SetWindowMode(WrapperEnum Mode)
{
	int count;
	if (Mode == WrapperEnum::Mode_Fullsceen)
		glfwSetWindowMonitor(window, glfwGetMonitors(&count)[0], (int)WindowPosition.x, (int)WindowPosition.y,
			(int)WindowSize.x, (int)WindowSize.y, 60);
	else
		glfwSetWindowMonitor(window, nullptr, (int)WindowPosition.x, (int)WindowPosition.y,
		(int)WindowSize.x, (int)WindowSize.y, 60);
}

void Application::SetWindowSize(const glm::vec2& WinSize)
{
	WindowSize = WinSize;
}

void Application::SetViewportSize(const glm::vec2& _ViewportSize)
{
	this->ViewportSize = _ViewportSize;
}

void Application::SetWindowTitle(const std::string& Title)
{
	glfwSetWindowTitle(window, Title.c_str());
}

void Application::SetWireFrameMode(const bool& Wireframe)
{
	this->Wireframe = Wireframe;
	if(Wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
