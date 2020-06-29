#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "AppLog.h"
#include "Global.h"


class Shader
{
private:
	bool CompiledStatus;
	unsigned int IndexInCache;
	unsigned int Program;
	std::string Name;
	std::string SystemPath;
	std::unordered_map<std::string, int> UniformLocationCache;
	static AppLog* Logger;
	static std::vector<std::shared_ptr<Shader>> Shaders;

	Shader(const std::string& ShaderName, const bool& EnableGeometryShader = false);
	unsigned int CompileShader(ShaderEnum type);
	unsigned int GetUniformLocation(const std::string& UniformName);
	ShaderEnum CompileStatus(unsigned int Shader);
	std::string ReadShaderFromFile(ShaderEnum type);
	static std::shared_ptr<Shader> FindExisiting(const std::string& ShaderName);

public:
	static std::shared_ptr<Shader> Add(const std::string& ShaderName, const bool& EnableGeometryShader = false);
	static std::shared_ptr<Shader> Get(const std::string& ShaderName);
	~Shader();

	unsigned int GetShaderProgram() const;
	std::string GetShaderPackagePath() const;

	void Bind();
	void Unbind();

	void SetUniform(const std::string& UniformName, const int& value);
	void SetUniform(const std::string& UniformName, const float& value);
	void SetUniform(const std::string& UniformName, const float& value1, const float& value2);
	void SetUniform(const std::string& UniformName, const float& value1, const float& value2, const float& value3);
	void SetUniform(const std::string& UniformName, const float& value1, const float& value2, const float& value3, const float& value4);
	void SetUniform(const std::string& UniformName, const glm::vec2& value);
	void SetUniform(const std::string& UniformName, const glm::vec3& value);
	void SetUniform(const std::string& UniformName, const glm::vec4& value);
	void SetUniform(const std::string& UniformName, const glm::mat3& value);
	void SetUniform(const std::string& UniformName, const glm::mat4& value);
};
