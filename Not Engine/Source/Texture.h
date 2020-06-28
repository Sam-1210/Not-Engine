#pragma once
#include <string>
#include <unordered_map>

static struct Flags
{
	bool Repeat;
	bool Mirrored_Repeat;
	bool Scale;
};

class Texture
{
private:
	Flags TextureFlags;
	int TexWidth, TexHeight, TexBitsPerPix;
	std::string DataPath;
	unsigned int ID;
	unsigned char* Image;
	void SetTexture();

	static unsigned int InstanceCounter;
	static std::unordered_map<std::string, unsigned int> TextureCache;

	/** Custom Destructor that will delete all textures in VRAM*/
	static void FreeTextureCache();
public:
	/** Creates An Empty Texture*/
	Texture();
	/** Creates Texture from file*/
	Texture(const std::string& Path);
	/** Loads Texture From Specified Package*/
	~Texture();

	void SetTextureData(const std::string& TexturePath);
	void BindAtSlot(unsigned int Slot = 0) const;
	void Unbind();

	inline unsigned int GetTextureID() const { return this->ID; }
	inline int GetImageHeight() const { return this->TexHeight; }
	inline int GetImageWidth() const { return this->TexWidth; }
	inline std::string GetImagePath() const { return this->DataPath; }
	//inline unsigned char* GetImageData() const { return this->Image; }
};