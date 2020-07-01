#pragma once
#include <string>

struct GLFWwindow;
struct GLFWimage;

class WindowLayer
{
private:
	GLFWwindow* mWindow;
	GLFWimage* Icon;
	std::string mName;
public:
	WindowLayer(const std::string& Name, const int& width, const int& height);

};
