#pragma once
#include "Node2D.h"

class Camera;

class Rect2D : public Node2D
{
protected:
	bool isTransparent;
	//Texture tex;
	//Mesh mesh;
	static bool BuffersSet;
	static unsigned int Rect2D_Instances;
	static unsigned int VBO;
	static unsigned int VAO;
	static float vertices[24];
	glm::mat4 Mat_Model;
	glm::mat4 Mat_View;
	glm::mat4 Mat_Projection;

	static void SetBuffers();
	static void FreeBuffers();
public:
	Rect2D(const std::string NodeName);
	~Rect2D();
	
	inline void EnableTransparency() { this->isTransparent = true; }
	inline void DisableTransparency() { this->isTransparent = false; }

	virtual void PropertyEditor() = 0;
	virtual void _process();
	virtual void _update(Camera* SceneCam);
	virtual void _render() = 0;
};

