#pragma once
#include "Node2D.h"

class Rect2D : public Node2D
{
protected:
	bool isTransparent;
	//Texture tex;
	//Mesh mesh;
	static bool BuffersSet;
	static unsigned int ID;
	static unsigned int VAO;
	static float vertices[24];
	glm::mat4 Mat_Model;
	glm::mat4 Mat_View;
	glm::mat4 Mat_Projection;

	static void SetBuffers();
public:
	Rect2D(const std::string NodeName);
	~Rect2D();
	
	inline void EnableTransparency() { this->isTransparent = true; }
	inline void DisableTransparency() { this->isTransparent = false; }

	virtual void PropertyEditor() = 0;
	virtual void _process();
	virtual void _update();
	virtual void _render() = 0;
};

