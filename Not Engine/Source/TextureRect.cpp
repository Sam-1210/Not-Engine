#include "TextureRect.h"
#include "Application.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

TextureRect::TextureRect() : Rect2D("TextureRect")
{
	mShader = Shader::Add("TextureRect");
	TextureData = nullptr;
}

TextureRect::TextureRect(const std::string& Name)
	: Rect2D(Name)
{
	mShader = Shader::Add("TextureRect");
	TextureData = nullptr;
}

TextureRect::TextureRect(const std::string& Name, const std::string& TexturePath)
	:Rect2D(Name)
{
	mShader = Shader::Add("TextureRect");
	TextureData = std::shared_ptr<Texture>(new Texture(TexturePath));
}

TextureRect::~TextureRect()
{
}

void TextureRect::Save(std::ofstream& SceneFile)
{
	SceneFile << "TextureRect ";
	if (Parent)
		SceneFile << Parent->GetID() << " ";
	SceneFile << Name << " ";
	SceneFile << ID << " ";
	SceneFile << Visible << " ";
	SceneFile << Rotation << " ";
	SceneFile << Position.x << " " << Position.y << " ";
	SceneFile << Scale.x << " " << Scale.y << " ";
	SceneFile << TextureData->GetImagePath();
	SceneFile << "\n";
}

void TextureRect::Load(std::ifstream& SceneFile)
{
	Node2D::Load(SceneFile);
	std::string TexturePath;
	SceneFile >> TexturePath;
	ChangeTexture(TexturePath);
}

void TextureRect::_process()
{
}

void TextureRect::_update()
{
	Rect2D::_update();
}

void TextureRect::_render()
{
	mShader->Bind();
	glBindVertexArray(VAO);

	glm::mat4 MVP = Mat_Projection * Mat_View * Mat_Model;

	mShader->SetUniform("MVP", MVP);
	TextureData->BindAtSlot();
	if (isTransparent)
		mShader->SetUniform("Transparent", 1);
	else
		mShader->SetUniform("Transparent", 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
