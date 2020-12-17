#pragma once
#include <string>
#include "NotKeyCodes.h"

struct GLFWwindow;

class WindowLayer
{
private:
	bool mVSync;
	float mAspectRatio;
	int mWidth;
	int mHeight;
	int mPosX;
	int mPosY;
	std::string mName;
	GLFWwindow* mWindow;

	static WindowLayer* CurrentContextLayer;
	static void ResizeWindowHandler(GLFWwindow* Window, int Width, int Height);
public:
	inline static WindowLayer* GetCurrentContext() { return CurrentContextLayer; }
public:
	bool is_FullScreen=0;
public:
	WindowLayer(const std::string& Name, const int& width, const int& height, const bool& Vsync = true, const std::string& Path = "");
	virtual ~WindowLayer();

	void MakeCurrentContext();
	void Resize(const int& width, const int& height);
	void Mode_FullScreen();
	void Mode_Windowed();
	void PollEvents();
	void SwapBuffers();
	void Close();

	bool isOpen() const;
	bool isKeyPressed(NotKeyCodes Key);
	int GetWidth();
	int GetHeight();
	int GetPosX();
	int GetPosY();
	float GetAspectRatio();
	inline GLFWwindow* GetRawWindow() const { return mWindow; }
	inline std::string GetWindowName() const { return mName; }

	void SetVsync(const bool& EnableVsync);
	void SetName(const std::string& Name);
	void SetPosition(const int& PosX, const int& PosY);
	void SetIcon(const std::string& IconPath);
};
