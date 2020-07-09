#pragma once

class FrameBuffer
{
private:
	unsigned int mFBO;
	unsigned int mColorTex;
	unsigned int mDepthTex;
	unsigned int mWidth;
	unsigned int mHeight;
	void Create();
public:
	FrameBuffer(const int& width, const int& height);
	~FrameBuffer();

	inline unsigned int GetColorTexture() { return mColorTex; }
	inline unsigned int GetDepthTexture() { return mDepthTex; }
	inline void Resize(const int& width, const int& height) 
	{
		this->mWidth = width;
		this->mHeight = height;
		Create(); 
	}
	void Bind();
	void Unbind();
};
