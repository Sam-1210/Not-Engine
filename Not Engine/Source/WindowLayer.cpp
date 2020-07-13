#include "WindowLayer.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>
#include <stb_image.h>

void WindowLayer::ResizeWindowHandler(GLFWwindow* Window, int Width, int Height)
{
    NE_CORE_WARN("Implementation Pending");
    //Issue Window Resized Event
}

WindowLayer::WindowLayer(const std::string& Name, const int& width, const int& height, const bool& Vsync, const std::string& Path)
{
    std::cout << "\t\t\t\t\t:::::::: NotEngine ::::::::\n\n\n\n";
    Logger::Init();
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

void WindowLayer::Mode_FullScreen()
{
    NE_CORE_WARN("Implementation Pending.");
}

void WindowLayer::Mode_Windowed()
{
    NE_CORE_WARN("Implementation Pending.");
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

GLFWwindow* WindowLayer::GetCurrentContext()
{
    return glfwGetCurrentContext();
}
