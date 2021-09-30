#include "Shader.h"
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

std::vector<std::shared_ptr<Shader>> Shader::Shaders;

unsigned int Shader::CompileShader(ShaderEnum type)
{
	unsigned int Compiled_Shader = 0;
	const std::string ReadData = ReadShaderFromFile(type);
	const char* Shader_Source = ReadData.c_str();
	ShaderEnum Status;

	if (type == ShaderEnum::Shader_Vertex)
		Compiled_Shader = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderEnum::Shader_Fragment)
		Compiled_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	else if (type == ShaderEnum::Shader_Geometry)
		Compiled_Shader = glCreateShader(GL_GEOMETRY_SHADER);

	glShaderSource(Compiled_Shader, 1, &Shader_Source, NULL);
	glCompileShader(Compiled_Shader);

	Status = CompileStatus(Compiled_Shader);
	if (Status == ShaderEnum::Compile_Failed)
	{
		glDeleteShader(Compiled_Shader);
		return 0;
	}

	return Compiled_Shader;
}

unsigned int Shader::GetUniformLocation(const std::string& UniformName)
{
	if (UniformLocationCache.find(UniformName) != UniformLocationCache.end()) {
		return UniformLocationCache[UniformName];
	}

	int loc = glGetUniformLocation(Program, UniformName.c_str());

	if (loc == -1)
		NE_CORE_WARN("<Warning> Uniform: " + UniformName + " Doesn't Exist");
	UniformLocationCache[UniformName] = loc;

	return loc;
}

std::shared_ptr<Shader> Shader::FindExisiting(const std::string& ShaderName)
{
	for (std::shared_ptr<Shader> Compiled : Shaders)
		if (Compiled->Name == ShaderName)
			return Compiled;
	return nullptr;
}

ShaderEnum Shader::CompileStatus(unsigned int Shader)
{
	int compileResults;
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &compileResults);

	if (compileResults == GL_FALSE) {
		int logLength;
		glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &logLength);

		char* compileLog = new char[logLength]; //(char*)alloca(logLength * sizeof(char));
		glGetShaderInfoLog(Shader, logLength, &logLength, compileLog);

		NE_CORE_ERROR("SHADER COMPILE ERROR : " + std::string(compileLog));

		delete[] compileLog;

		CompiledStatus &= false;
		return ShaderEnum::Compile_Failed;
	}
	CompiledStatus &= true;

	return ShaderEnum::Compile_Success;
}

std::string Shader::ReadShaderFromFile(ShaderEnum type)
{
	std::string code;
	std::ifstream stream;
	std::stringstream buffer;

	if (type == ShaderEnum::Shader_Vertex)
		stream.open(SystemPath + Name +".vs", std::fstream::in);
	else if (type == ShaderEnum::Shader_Fragment)
		stream.open(SystemPath + Name + ".fs", std::fstream::in);
	else if (type == ShaderEnum::Shader_Geometry)
		stream.open(SystemPath + Name + ".gs", std::fstream::in);

	while (std::getline(stream, code)) {
		buffer << code << "\n";
	}
	//std::cout << buffer.str() << std::endl; //Show shader content on screen
	return buffer.str();
}

std::shared_ptr<Shader> Shader::Add(const std::string& ShaderName, const bool& EnableGeometryShader)
{
	std::shared_ptr<Shader> ExistingShader = FindExisiting(ShaderName);
	if (ExistingShader)
		return ExistingShader;
	else
		return std::shared_ptr<Shader>(new Shader(ShaderName, EnableGeometryShader));
}

std::shared_ptr<Shader> Shader::Get(const std::string& ShaderName)
{
	return FindExisiting(ShaderName);
}

Shader::Shader(const std::string& ShaderName, const bool& EnableGeometryShader)
{
	CompiledStatus = true;

	unsigned int Compiled_VS, Compiled_FS, Compiled_GS;
	Program = glCreateProgram();
	
	Name = ShaderName;
	SystemPath = EnginePath::ShaderFolder + ShaderName + "/";

	Compiled_VS = CompileShader(ShaderEnum::Shader_Vertex);
	Compiled_FS = CompileShader(ShaderEnum::Shader_Fragment);
	
	if(EnableGeometryShader){
		Compiled_GS = CompileShader(ShaderEnum::Shader_Geometry);
		glAttachShader(Program, Compiled_GS);
	}
	
	glAttachShader(Program, Compiled_VS);
	glAttachShader(Program, Compiled_FS);
	glValidateProgram(Program);
	glLinkProgram(Program);

	glDeleteShader(Compiled_VS);
	if(EnableGeometryShader)
		glDeleteShader(Compiled_GS);
	glDeleteShader(Compiled_FS);

	if(CompiledStatus)
		NE_CORE_INFO("Compiled Shader \"" + Name + "\" Successfully");
	else
		NE_CORE_CRITICAL("Compiling Shader \"" + Name + "\" Failed");

	IndexInCache = Shaders.size();
	Shaders.push_back(std::shared_ptr<Shader>(this));
}

Shader::~Shader()
{
	Shaders.erase(Shaders.begin() + IndexInCache);
	glDeleteProgram(Program);
}

unsigned int Shader::GetShaderProgram() const
{
	return Program;
}

std::string Shader::GetShaderPackagePath() const
{
	return SystemPath;
}

void Shader::Bind()
{
	glUseProgram(Program);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform(const std::string& UniformName, const int& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform1i(location, value);
}

void Shader::SetUniform(const std::string& UniformName, const float& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform1f(location, value);
}

void Shader::SetUniform(const std::string& UniformName, const float& value1, const float& value2)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform2f(location, value1, value2);
}

void Shader::SetUniform(const std::string& UniformName, const float& value1, const float& value2, const float& value3)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform3f(location, value1, value2, value3);
}

void Shader::SetUniform(const std::string& UniformName, const float& value1, const float& value2, const float& value3, const float& value4)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform4f(location, value1, value2, value3, value4);
}

void Shader::SetUniform(const std::string& UniformName, const glm::vec2& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform2f(location, value.x, value.y);
}

void Shader::SetUniform(const std::string& UniformName, const glm::vec3& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& UniformName, const glm::vec4& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string& UniformName, const glm::mat3& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& UniformName, const glm::mat4& value)
{
	unsigned int location = GetUniformLocation(UniformName);
	if (location == -1)
		return;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
