#include "TextureRect.h"
#include "Application.h"
#include "Editor.h"
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

TextureRect::TextureRect() : Rect2D("TextureRect")
{
	TextureShader = Shader::Add("TextureRect");
	TextureData = nullptr;
}

TextureRect::TextureRect(const std::string& Name)
	: Rect2D(Name)
{
	TextureShader = Shader::Add("TextureRect");
	TextureData = nullptr;
}

TextureRect::TextureRect(const std::string& Name, const std::string& TexturePath)
	:Rect2D(Name)
{
	TextureShader = Shader::Add("TextureRect");
	TextureData = std::shared_ptr<Texture>(new Texture(TexturePath));
}

TextureRect::~TextureRect()
{
}

void TextureRect::PropertyEditor()
{
	Node2D::PropertyEditor();

	static bool isNotCollapsed = true;
	ImGui::SetNextItemOpen(isNotCollapsed);
	if (ImGui::CollapsingHeader("TextureRect"))
	{
		ImGui::Checkbox("Transparent", &isTransparent);
		isNotCollapsed = true;
		ImGui::Text("Preview Texture");
		ImTextureID TexPreview = (void*)TextureData->GetTextureID();
		ImVec2 PanelSize = ImVec2(Editor::GetInstance()->GetRightPanelWidth() * 0.8, Editor::GetInstance()->GetRightPanelWidth() * 0.8);
		ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - PanelSize.x) / 2, ImGui::GetCursorPos().y));
		if(ImGui::ImageButton(TexPreview, PanelSize, ImVec2(0, 1), ImVec2(1, 0), 2, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
			LOG("Texture Menu with Flags")
	}
	else
		isNotCollapsed = false;
}

void TextureRect::_process()
{
}

void TextureRect::_update()
{
	glm::vec2 ViewportSize = Application::ActiveApplication->GetViewportSize();
	float AspectRatio = ViewportSize.x / ViewportSize.y;
	Mat_Projection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	Mat_Model = glm::mat4(1.0f);
	Mat_Model = glm::translate(Mat_Model, glm::vec3(this->Position, 0.0f));
	Mat_Model = glm::rotate(Mat_Model, glm::radians(this->Rotation), glm::vec3(0.0, 0.0, 1.0));
	Mat_Model = glm::scale(Mat_Model, glm::vec3(this->Scale, 1.0f));
}

void TextureRect::_render()
{
	if (isTransparent)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);

	TextureShader->Bind();
	glBindVertexArray(VAO);

	glm::mat4 MVP = Mat_Projection * Mat_View * Mat_Model;

	TextureShader->SetUniform("MVP", MVP);

	if (TextureData)
	{
		TextureData->BindAtSlot();
		TextureShader->SetUniform("Color", 0.0f);
	}
	else
		TextureShader->SetUniform("Color", 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
