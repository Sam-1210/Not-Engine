#pragma once
#include "Rect2D.h"
#include "Shader.h"
#include "Texture.h"

class TextureRect : public Rect2D
{
private:
	std::shared_ptr<Texture> TextureData;
	std::shared_ptr<Shader> mShader;

public:
	TextureRect();
	TextureRect(const std::string& Name);
	TextureRect(const std::string& Name, const std::string& TexturePath);

	~TextureRect();

	inline void ChangeTexture(const std::string& TexturePath) { TextureData = std::shared_ptr<Texture>(new Texture(TexturePath)); }

	inline std::shared_ptr<Texture> GetTexture() const { return this->TextureData; }
	inline std::shared_ptr<Shader> GetShader() { return this->mShader; }

	void PropertyEditor();

	void _process();
	void _update();
	void _render();
};
