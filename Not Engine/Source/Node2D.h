#pragma once
#include "Node.h"
#include <glm/glm.hpp>

class Node2D : public Node
{
protected:
	float Rotation;
	glm::vec2 Position;
	glm::vec2 Scale;

public:
	Node2D();
	Node2D(const std::string NodeName);
	Node2D(const std::string NodeName, const bool& isVisible, const bool& isProcess = false);

	inline void SetRotation(const float& NewRotaion) { this->Rotation = NewRotaion; }
	inline void SetPosition(const glm::vec2& NewPosition) { this->Position = NewPosition; }
	inline void SetPosition(const float& x, const float& y) { this->Position = glm::vec2(x, y); }
	inline void SetScale(const glm::vec2& NewScale) { this->Scale = NewScale; }
	inline void SetScale(const float& x, const float& y) { this->Scale = glm::vec2(x, y); }

	inline float GetRotation() const { return this->Rotation; }
	inline glm::vec2 GetPosition() const { return this->Position; }
	inline glm::vec2 GetScale() const { return this->Scale; }
	
	virtual void PropertyEditor();
};