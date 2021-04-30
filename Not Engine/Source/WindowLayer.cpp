#include "WindowLayer.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <stb_image.h>

void WindowLayer::ResizeWindowHandler(GLFWwindow* Window, int Width, int Height)
{
    NE_CORE_WARN("Implementation Pending");
    //Issue Window Resized Event
}

WindowLayer::WindowLayer(const std::string& Name, const int& width, const int& height, const bool& Vsync, const std::string& Path)
{
    mVSync = Vsync;
    mName = Name;
    mWidth = width;
    mHeight = height;
    
    if (!glfwInit())
    {
        NE_CORE_CRITICAL("Failed to Initialize Window Library.");
        bool GLFWInitialized = false;
        assert(GLFWInitialized == true);
    }

    mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), nullptr, nullptr);

    if (!mWindow)
    {
        NE_CORE_CRITICAL("Creation of \"{0}\" ({1},{2}) Window Failed.", mName, mWidth, mHeight);
        bool WindowCreated = false;
        assert(WindowCreated == true);
    }
   
    glfwMakeContextCurrent(mWindow);
    glfwSetWindowSizeCallback(mWindow, ResizeWindowHandler);

    if (Path != "")
    {
        if (std::filesystem::exists(Path))
        {
            GLFWimage tmpIcon;
            tmpIcon.pixels = stbi_load(Path.c_str(), &tmpIcon.width, &tmpIcon.height, nullptr, 4);
            glfwSetWindowIcon(mWindow, 1, &tmpIcon);
        }
        else
        {
            NE_CORE_WARN("Icon Path is Invalid.");
        }
    }

    NE_CORE_INFO("Created \"{0}\" ({1},{2}) Window Successfully.", mName, mWidth, mHeight); 
}

WindowLayer::~WindowLayer()
{
    glfwTerminate();
}

void WindowLayer::MakeCurrentContext()
{
    glfwMakeContextCurrent(mWindow);
}

void WindowLayer::Resize(const int& width, const int& height)
{
    mWidth = width;
    mHeight = height;
    glfwSetWindowSize(mWindow, width, height);
}

void WindowLayer::Mode_FullScreen()
{
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    if(monitor_index>=0 && monitor_index<=count){
        GLFWmonitor* monitor = monitors[monitor_index];
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        const char* name = glfwGetMonitorName(monitor);
        NE_CORE_INFO(std::string(count)+"monitor(s) found.")
        NE_CORE_INFO("using "+std::string(name)+"monitor.")
        glfwSetWindowMonitor(window,monitor,0, 0, mode->width, mode->height, mode->refreshRate);
	    bool is_FullScreen=1;
    } 
    NE_CORE_WARN("unrecogonized monitor number.");

}

void WindowLayer::Mode_Windowed()
{
    
	bool is_FullScreen=1;
    GLFWmonitor* monitor = glfwGetWindowMonitor(window);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window,nullptr,mPosX, mPosY, mWidth, mHeight, mode->refreshRate);

    NE_CORE_WARN("Implementation Pending.");
}

void WindowLayer::Close()
{
    glfwSetWindowShouldClose(mWindow, true);
}

bool WindowLayer::isOpen() const
{
    return !(glfwWindowShouldClose(mWindow));
}

int WindowLayer::GetWidth()
{
    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
    return mWidth;
}

int WindowLayer::GetHeight()
{
    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
    return mHeight;
}

int WindowLayer::GetPosX()
{
    glfwGetWindowPos(mWindow, &mPosX, &mPosY);
    return mPosX;
}

int WindowLayer::GetPosY()
{
    glfwGetWindowPos(mWindow, &mPosX, &mPosY);
    return mPosY;
}

float WindowLayer::GetAspectRatio()
{
    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
    return float(mWidth)/float(mHeight);
}

void WindowLayer::SetVsync(const bool& EnableVsync)
{
    EnableVsync ? glfwSwapInterval(1) : glfwSwapInterval(0);
}

void WindowLayer::SetName(const std::string& Name)
{
    mName = Name;
    glfwSetWindowTitle(mWindow, mName.c_str());
}

void WindowLayer::SetPosition(const int& PosX, const int& PosY)
{
    glfwSetWindowPos(mWindow, PosX, PosY);
    glfwGetWindowPos(mWindow, &mPosX, &mPosY);
}

void WindowLayer::SetIcon(const std::string& IconPath)
{
    if (std::filesystem::exists(IconPath))
    {
        GLFWimage tmpIcon;
        tmpIcon.pixels = stbi_load(IconPath.c_str(), &tmpIcon.width, &tmpIcon.height, nullptr, 4);
        glfwSetWindowIcon(mWindow, 1, &tmpIcon);
    }
    else
    {
        NE_CORE_WARN("Icon Path is Invalid.");
    }
}
