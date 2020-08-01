#pragma once
#include "../Math/Transform3D.h"
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"

namespace Entropy
{

	enum CameraMovement
	{
		CAMERA_FORWARD,
		CAMERA_BACKWARD,
		CAMERA_LEFT,
		CAMERA_RIGHT,
		CAMERA_UP,
		CAMERA_DOWN,
		WORLD_UP,
		WORLD_DOWN
	};

	class __declspec(dllexport) Camera
	{
	public:
		// Camera Attributes
		Math::Vec3 position;
		Math::Vec3 front;
		Math::Vec3 up;
		Math::Vec3 right;
		Math::Vec3 worldUp;

		// Camera Modifiers
		float yaw;
		float pitch;

		float mouseSensitivity;
		float zoom;

		Camera(Math::Vec3 position = Math::Vec3(), Math::Vec3 up = Math::Vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

		Math::Mat4 getViewMatrix();

		void updatePosition(CameraMovement direction, float deltaTime, float velocity = 2.5f);
		void updateRotation(float xOffset, float yOffset, bool constrainPitch = true, float minPitch = -89.0f, float maxPitch = 89.0f);
		void updateFOV(float offset);

		void updateVectors();
	};
}