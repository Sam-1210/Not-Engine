#include "FrameBuffer.h"
#include "Shader.h"
#include "Log.h"
#include <glad/glad.h>

void FrameBuffer::Create()
{
	if (!mFBO)
	{
		glDeleteFramebuffers(1, &mFBO);
		glDeleteTextures(1, &mColorTex);
		glDeleteTextures(1, &mDepthTex);
	}

	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	glGenTextures(1, &mColorTex);
	glBindTexture(GL_TEXTURE_2D, mColorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTex, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &mDepthTex);
	glBindTexture(GL_TEXTURE_2D, mDepthTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, 1280, 720);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		NE_CORE_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	Unbind();
}

FrameBuffer::FrameBuffer(const int& width, const int& height) 
	: mWidth(width), mHeight(height)
{
	Create();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &mFBO);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	glViewport(0, 0, mWidth, mHeight);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}