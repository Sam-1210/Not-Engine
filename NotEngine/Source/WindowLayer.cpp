#include "WindowLayer.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>
#include <stb_image.h>
#include "OpenGL_Core.h"

void WindowLayer::ResizeWindowHandler(GLFWwindow* Window, int Width, int Height)
{
    OpenGL::Core::SetViewportSize(0, 0, Width, Height);
}

WindowLayer::WindowLayer(const std::string& Name, int32_t width, int32_t height, bool Vsync, WindowModes Mode, const std::string& IconPath)
{
    std::cout << "\t\t\t\t\t:::::::: NotEngine ::::::::\n\n\n\n";
    Logger::Init();
    mVSync = Vsync;
    mName = Name;
    mWidth = width;
    mHeight = height;
    mMode = Mode;
    mPosX = 0;
    mPosY = 0;
    mAspectRatio = float(width) / float(height);
    
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
    SetVSync(mVSync);
    /// <issue>
    /// OpenGL is not loaded, hence if mode is full screen, monitor resolution >< window size, there will be callback to resize window, which will fail due to glViewport is null
    /// </issue>

    if (IconPath != "")
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

    NE_CORE_INFO("Created \"{0}\" ({1},{2}) Window Successfully.", mName, mWidth, mHeight); 
}

WindowLayer::~WindowLayer()
{
    NE_CORE_INFO("Window \"{0}\" Closed.", mName);
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

void WindowLayer::SwitchMode(WindowModes Mode)
{
    mMode = Mode;
    if (Mode == ModeWindowed)
    {
        glfwSetWindowMonitor(mWindow, NULL, GetPosX(), GetPosY(), mWidth, mHeight, GLFW_DONT_CARE);
    }
    else if (Mode == ModeBorderlessWindow)
    {
        NE_CORE_WARN("Feature Not Tested : Borderless Window");
        int count;
        int monitorIndex = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        if (monitorIndex >= 0 && monitorIndex <= count)
        {
            GLFWmonitor* monitor = monitors[monitorIndex];
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            const char* name = glfwGetMonitorName(monitor);
            NE_CORE_INFO(std::to_string(count) + " monitor(s) found.");
            NE_CORE_INFO("Using monitor : " + std::string(name));
            glfwSetWindowMonitor(mWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
            NE_CORE_WARN("Unrecogonized monitor number.");
    }
    else if (Mode == ModeFullscreen)
    {
        /// <FeatureNotice>
        /// As of now by default our monitor is monitor[0], support for additional monitors will be added in future.
        /// </Feature Notice>
        int count;
        int monitorIndex = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        if (monitorIndex >= 0 && monitorIndex <= count)
        {
            GLFWmonitor* monitor = monitors[monitorIndex];
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            const char* name = glfwGetMonitorName(monitor);
            NE_CORE_INFO(std::to_string(count) + " monitor(s) found.");
            NE_CORE_INFO("Using monitor : " + std::string(name));
            NE_CORE_INFO(mode->width);
            glfwSetWindowMonitor(mWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
            NE_CORE_WARN("Unrecogonized monitor number.");

    }
    else
    {
        NE_CORE_ERROR("Unidentified Window Mode, falling back to Windowed Mode!!!");
        SwitchMode(ModeWindowed);
    }
    SetVSync(mVSync);   //Preserve VSync after Switching Mode
}

void WindowLayer::PollEvents()
{
    glfwPollEvents();
}

void WindowLayer::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
}

void WindowLayer::Close()
{
    glfwSetWindowShouldClose(mWindow, true);
}

bool WindowLayer::isOpen() const
{
    return !(glfwWindowShouldClose(mWindow));
}

bool WindowLayer::isKeyPressed(NotKeyCodes Key)
{
    return (glfwGetKey(mWindow, (int)Key) == GLFW_PRESS);
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

void WindowLayer::SetVSync(const bool& EnableVsync)
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
