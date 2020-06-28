#include "Global.h"

std::string EngineError::ChildWithSameNameExists = "ChildWithSameNameExists";

std::string EnginePath::AssetsFolder = "./Assets/";
std::string EnginePath::MaterialFolder = EnginePath::AssetsFolder + "Materials/";
std::string EnginePath::ShaderFolder = EnginePath::MaterialFolder + "Shaders/";
std::string EnginePath::TextureFolder = EnginePath::MaterialFolder + "Textures/";
std::string EnginePath::FontsFolder = EnginePath::AssetsFolder + "Fonts/";