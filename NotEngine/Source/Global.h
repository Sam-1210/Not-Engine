#pragma once
#include <string>
#include <vector>
#define LOG_D(MSG, FILE)
#define LOG_R(MSG, FILE)

enum class MyStatus : unsigned int
{
	GLFW_Init_Error,
	Window_Creation_Error,
	GLAD_Init_Error, 
	Init_Success,
	Already_Initialized,
	SuccessChildAdded,
	SuccessChildRemove,
	SuccessReparent,
	ErrChildRemove,
	ErrException, 
	ErrNoParent,
	ErrIndexOutOfBounds,
};

enum class WrapperEnum : unsigned int
{
	Mode_Windowed,
	Mode_BorderlessFullscreen,
	Mode_Fullsceen,
};

enum class SceneType : unsigned int
{
	Scene_2D,
	Scene_3D,
};

enum class ShaderEnum : unsigned int
{
	Shader_Vertex,
	Shader_Fragment,
	Shader_Geometry,
	Compile_Failed,
	Compile_Success,
};

namespace EnginePath
{
	extern std::string AssetsFolder;
	extern std::string ShaderFolder;
	extern std::string MaterialFolder;
	extern std::string TextureFolder;
	extern std::string FontsFolder;
}

namespace EngineError
{
	extern std::string ChildWithSameNameExists;
}
