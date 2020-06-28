#pragma once
#include "Rect2D.h"

class Shader;

class ColorRect : public Rect2D
{
private:
	glm::vec4 RectColor;
	std::shared_ptr<Shader> ColorShader;

public:
	ColorRect();
	ColorRect(const std::string& Name);
	ColorRect(const std::string& Name, const glm::vec4& Color);

	~ColorRect() {};

	inline void SetColor(const glm::vec4& NewColor) { this->RectColor = NewColor; }

	inline glm::vec4 GetColor() const { return RectColor; }
	inline std::shared_ptr<Shader> GetShader() const { return ColorShader; }

	void PropertyEditor();
	void _process();
	void _update();
	void _render();
};
