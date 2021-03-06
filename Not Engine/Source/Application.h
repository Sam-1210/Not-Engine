#pragma once
#include "Global.h"
#include "Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Engine;

class Application
{
protected:
	bool Initialized;
	bool Resizable;
	bool VSync;
	bool Wireframe;
	int ID;
	Engine* engine;
	glm::vec2 GL_Version;
	glm::vec2 WindowPosition;
	glm::vec2 WindowSize;
	glm::vec2 ViewportSize;
	GLFWimage IconRes;
	GLFWwindow* window;
	std::string WindowTitle;
	WrapperEnum WindowMode;
	static int InstanceCounter;
public:
	/** Creates Window with res 800x600 and Title "Application", with windowed mode, 
		resizable true, VSync and Wireframe false, also turns on Logging */
	Application();
	/** WinSize : Vec2<int>(width, height). GL_Version  : Vector2<int>(MaxVersion, Min Version) */
	Application(const std::string& WinTitle, const glm::vec2& _WinSize, const glm::vec2 WinPos, 
		const glm::vec2& _GL_Version, const bool& Logging = false,
		const bool& _Resizable = true, const bool& _VerticalSync = false, 
		const WrapperEnum& WinMode = WrapperEnum::Mode_Windowed, const bool& _Wireframe = false);
	~Application();
	/*---------------------------------Utility Func-----------------------------------*/
	MyStatus Init();
	void Exit();
	static Application* ActiveApplication;
	static void ResizeWindowHandler(GLFWwindow* Window, int w, int h);
	static void SetContextCurrent(Application* App);
	/*-----------------------------------Getters--------------------------------------*/
	bool GetVSync() const;
	bool IsResizable() const;
	bool IsWireframe() const;
	bool WindowIsNotClosed() const;
	Engine* GetEngine() const;
	glm::vec2 GetGL_Version() const;
	glm::vec2 GetWindowSize() const;
	glm::vec2 GetViewportSize() const;
	GLFWwindow* GetWindowObject() const;
	WrapperEnum GetWindowMode() const;
	std::string GetWindowTitle() const;

	inline const char* GetVendor() const { return (const char*)glGetString(GL_VENDOR); }
	inline const char* GetRenderer() const { return (const char*)glGetString(GL_RENDERER); }
	inline const char* GetVersion() const { return (const char*)glGetString(GL_VERSION); }
	/*------------------------------------Setters--------------------------------------*/
	void EnableTransparency();
	void DisableTransparency();
	void SetDepthTest(const bool& DepthTest);
	void SetResizable(const bool& Resizable);
	void SetVSync(const bool& VerticalSync);
	void SetWindowMode(WrapperEnum Mode);
	void SetWindowSize(const glm::vec2& WinSize);
	inline void SetViewportSize(const float& Width, const float& Height) { this->ViewportSize = glm::vec2(Width, Height); }
	void SetViewportSize(const glm::vec2& _ViewportSize);
	void SetWindowTitle(const std::string& Title);
	void SetWireFrameMode(const bool& Wireframe);
};

