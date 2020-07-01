#include "Texture.h"
#include "Log.h"
#include <stb_image.h>
#include <glad/glad.h>

unsigned int Texture::InstanceCounter = 0;
std::unordered_map<std::string, unsigned int> Texture::TextureCache;

Texture::Texture() :  TexWidth(0), TexHeight(0), TexBitsPerPix(0), ID(0), Image(nullptr)
{
	++InstanceCounter;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	XFlipped = false;
	YFlipped = false;
}

Texture::Texture(const std::string& Path) : TexWidth(0), TexHeight(0), TexBitsPerPix(0), DataPath(Path), ID(0), Image(nullptr)
{
	++InstanceCounter;
	if (TextureCache.find(Path) != TextureCache.end())
	{
		this->ID = TextureCache[Path];
		return;
	}
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SetTexture();

	TextureCache[DataPath] =  ID;
}

Texture::~Texture()
{
	--InstanceCounter;
	stbi_image_free(Image);
	if (!InstanceCounter)
		FreeTextureCache();
}

void Texture::FlipX()
{
	XFlipped = XFlipped ? false : true;
	//SetTexture();
}

void Texture::FlipY()
{
	YFlipped = YFlipped ? false : true;
	///SetTexture();
}

void Texture::SetTexture()
{
	stbi_set_flip_vertically_on_load(1);
	
	if(Image)
		stbi_image_free(Image);

	Image = stbi_load(DataPath.c_str(), &TexWidth, &TexHeight, &TexBitsPerPix, 4);

	if (!Image)
		NE_CORE_CRITICAL("No Texture Exists at Path : " + DataPath);

	int nrComponents = TexBitsPerPix;
	GLenum format;
	if (nrComponents == 1)
		format = GL_RED;
	else if (nrComponents == 3)
		format = GL_RGB;
	else if (nrComponents == 4)
		format = GL_RGBA;
	else
		format = GL_RGBA8;

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TexWidth, TexHeight, 0, format, GL_UNSIGNED_BYTE, Image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::FreeTextureCache()
{
	for (auto Cache : TextureCache)
		glDeleteTextures(1, &Cache.second);
}

void Texture::SetTextureData(const std::string& TexturePath)
{
	DataPath = TexturePath;
	if (TextureCache.find(DataPath) != TextureCache.end())
	{
		this->ID = TextureCache[DataPath];
		return;
	}
	SetTexture();
}

void Texture::BindAtSlot(unsigned int Slot) const
{
	glActiveTexture(GL_TEXTURE0 + Slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
