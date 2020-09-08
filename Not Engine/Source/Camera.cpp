#include "Camera.h"
#include "NotKeyCodes.h"

Camera::Camera(float AspectRatio)
{
	mProjection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	mView = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::onResize(float AspectRatio)
{
	mProjection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	mView = glm::mat4(1.0f);

	//static float x = 0.0f, y = 0.0f, scale = 1.0f, speed = 0.01f;
	//if (mAppLayer->isKeyPressed(NotKeyCodes::NOT_KEY_W))
	//	y -= speed;
	//if (mAppLayer->isKeyPressed(NotKeyCodes::NOT_KEY_S))
	//	y += speed;
	//if (mAppLayer->isKeyPressed(NotKeyCodes::NOT_KEY_A))
	//	x += speed;
	//if (mAppLayer->isKeyPressed(NotKeyCodes::NOT_KEY_D))
	//	x -= speed;
	//if (mAppLayer->isKeyPressed(NotKeyCodes::NOT_KEY_UP))
	//	scale -= speed;
	//if (mAppLayer->isKeyPressed(NotKeyCodes::NOT_KEY_DOWN))
	//	scale += speed;
	//
	//mView = glm::translate(mView, glm::vec3(x, y, 0.0f));
	//mView = glm::scale(mView, glm::vec3(scale));
}
