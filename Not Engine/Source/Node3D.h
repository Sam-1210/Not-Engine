#pragma once
#include "Node.h"
#include "glm.hpp"

class Node3D : public Node
{
private:
	glm::vec3 Rotation;
	glm::vec3 Position;
	glm::vec3 Scale;
public:
	Node3D();
	Node3D(const std::string NodeName);
	Node3D(const std::string NodeName, const bool& isVisible, const bool& isProcess = false);

	inline void SetRotation(const glm::vec3& NewRotaion) { this->Rotation = NewRotaion; }
	inline void SetPosition(const glm::vec3& NewPosition) { this->Position = NewPosition; }
	inline void SetScale(const glm::vec3& NewScale) { this->Scale = Scale; }

	inline glm::vec3 GetRotation() const { return this->Rotation; }
	inline glm::vec3 GetPosition() const { return this->Position; }
	inline glm::vec3 GetScale() const { return this->Scale; }
};