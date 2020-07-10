#pragma once
#include "Rect2D.h"
#include <memory>

class Shader;

class ColorRect : public Rect2D
{
private:
	glm::vec3 RectColor;
	float Alpha;
	std::shared_ptr<Shader> mShader;

public:
	ColorRect();
	ColorRect(const std::string& Name);
	ColorRect(const std::string& Name, const glm::vec4& Color);

	~ColorRect() {};

	inline void SetColor(const glm::vec3& NewColor) { this->RectColor = NewColor; }
	inline void SetAlpha(const float& NewAlpha) { this->Alpha = NewAlpha; }
	inline void SetColor(const glm::vec4& NewColor) { this->RectColor = glm::vec3(NewColor); this->Alpha = NewColor.a; }

	inline glm::vec3 GetColor() const { return RectColor; }
	inline float GetAlpha() { return this->Alpha; }
	inline std::shared_ptr<Shader> GetShader() const { return mShader; }

	void PropertyEditor() override;
	void Save(std::ofstream& SceneFile) override;
	void Load(std::ifstream& SceneFile) override;
	void _process() override;
	void _update() override;
	void _render() override;
};
