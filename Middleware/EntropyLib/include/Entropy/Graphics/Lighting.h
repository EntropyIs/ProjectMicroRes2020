#pragma once

#include "../Math/Vec3.h"

namespace Entropy
{
	namespace Graphics
	{
		struct __declspec(dllexport) DirectionalLight
		{
			Math::Vec3 Direction;

			Math::Vec3 Ambient;
			Math::Vec3 Diffuse;
			Math::Vec3 Specular;

			DirectionalLight(const Math::Vec3& direction, const Math::Vec3& Ambient, const Math::Vec3& diffuse, const Math::Vec3& specular) : Direction(direction), Ambient(Ambient), Diffuse(diffuse), Specular(specular) {};
			DirectionalLight(float i, float j, float k, float aI, float aJ, float aK, float dI, float dJ, float dK, float sI, float sJ, float sK) : Direction(i, j, k), Ambient(aI, aJ, aK), Diffuse(dI, dJ, dK), Specular(sI, sJ, sK) {};
			DirectionalLight(float i, float j, float k, float ambient, float diffuse, float specular) :Direction(i, j, k), Ambient(ambient, ambient, ambient), Diffuse(diffuse, diffuse, diffuse), Specular(specular, specular, specular) {};
		};

		struct __declspec(dllexport) PointLight
		{
			Math::Vec3 Position;

			float Constant;
			float Linear;
			float Quadratic;

			Math::Vec3 Ambient;
			Math::Vec3 Diffuse;
			Math::Vec3 Specular;

			PointLight(const Math::Vec3& position, float constant, float linear, float quadratic, const Math::Vec3& Ambient, const Math::Vec3& diffuse, const Math::Vec3& specular) : Position(position), Constant(constant), Linear(linear), Quadratic(quadratic), Ambient(Ambient), Diffuse(diffuse), Specular(specular) {};
			PointLight(float i, float j, float k, float constant, float linear, float quadratic, float aI, float aJ, float aK, float dI, float dJ, float dK, float sI, float sJ, float sK) : Position(i, j, k), Constant(constant), Linear(linear), Quadratic(quadratic), Ambient(aI, aJ, aK), Diffuse(dI, dJ, dK), Specular(sI, sJ, sK) {};
			PointLight(float i, float j, float k, float constant, float linear, float quadratic, float ambient, float diffuse, float specular) : Position(i, j, k), Constant(constant), Linear(linear), Quadratic(quadratic), Ambient(ambient, ambient, ambient), Diffuse(diffuse, diffuse, diffuse), Specular(specular, specular, specular) {};
		};

		struct __declspec(dllexport) SpotLight
		{
			Math::Vec3 Position;
			Math::Vec3 Direction;

			float InnerCutOff;
			float OuterCutOff;

			Math::Vec3 Ambient;
			Math::Vec3 Diffuse;
			Math::Vec3 Specular;

			SpotLight(const Math::Vec3& position, const Math::Vec3& direction, float innerCutOff, float outerCutOff, const Math::Vec3& Ambient, const Math::Vec3& diffuse, const Math::Vec3& specular) : Position(position), Direction(direction), InnerCutOff(innerCutOff), OuterCutOff(outerCutOff), Ambient(Ambient), Diffuse(diffuse), Specular(specular) {};
			SpotLight(float i, float j, float k, float dirI, float dirJ, float dirK, float innerCutOff, float outerCutOff, float aI, float aJ, float aK, float dI, float dJ, float dK, float sI, float sJ, float sK) : Position(i, j, k), Direction(dirI, dirJ, dirK), InnerCutOff(innerCutOff), OuterCutOff(outerCutOff), Ambient(aI, aJ, aK), Diffuse(dI, dJ, dK), Specular(sI, sJ, sK) {};
			SpotLight(float i, float j, float k, float dirI, float dirJ, float dirK, float innerCutOff, float outerCutOff, float ambient, float diffuse, float specular) : Position(i, j, k), Direction(dirI, dirJ, dirK), InnerCutOff(innerCutOff), OuterCutOff(outerCutOff), Ambient(ambient, ambient, ambient), Diffuse(diffuse, diffuse, diffuse), Specular(specular, specular, specular) {};
		};
	}
}