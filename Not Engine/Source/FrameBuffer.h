#pragma once
#include <string>
#include <memory>

class Shader;

class FrameBuffer
{
private:
	unsigned int FBO;
	unsigned int RBO;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int ColorTex;
	unsigned int DepthTex;

	float frameBufferCoord[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	std::shared_ptr<Shader> mShader;
public:
	FrameBuffer(const std::string& ShaderName = "FrameBuffer");
	~FrameBuffer();

	inline unsigned int GetColorTexture() { return ColorTex; }
	inline unsigned int GetDepthTexture() { return DepthTex; }
	void Bind();
	void Unbind();
	void RenderFrameBuffer();
};
