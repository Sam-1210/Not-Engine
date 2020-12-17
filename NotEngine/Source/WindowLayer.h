#pragma once
#include <string>
#include "Core.h"
#include "NotKeyCodes.h"

struct GLFWwindow;

enum WindowModes : int16_t
{
	ModeWindowed = 1,
	ModeBorderlessWindow = LSH(1),
	ModeFullscreen = LSH(2),
};

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
	WindowModes mMode;

	static WindowLayer* CurrentContextLayer;
	static void ResizeWindowHandler(GLFWwindow* Window, int Width, int Height);

public:
	WindowLayer(const std::string& Name, int32_t width, int32_t height, bool Vsync = true, WindowModes Mode = ModeWindowed, const std::string& IconPath = "");
	virtual ~WindowLayer();

	void MakeCurrentContext();
	void Resize(const int& width, const int& height);
	void SwitchMode(WindowModes Mode);
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
	inline static WindowLayer* GetCurrentContext() { return CurrentContextLayer; }

	void SetVSync(const bool& EnableVsync);
	void SetName(const std::string& Name);
	void SetPosition(const int& PosX, const int& PosY);
	void SetIcon(const std::string& IconPath);
};
