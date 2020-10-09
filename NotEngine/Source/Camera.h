#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::mat4 mProjection;
	glm::mat4 mView;

public:
	Camera(float AspectRatio);
	~Camera();

	void onResize(float AspectRatio);
	inline glm::mat4 GetProjection() const { return mProjection; }
	inline glm::mat4 GetView() const { return mView; }
};
