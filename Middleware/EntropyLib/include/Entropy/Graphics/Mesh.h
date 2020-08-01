#pragma once

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

#include "Material.h"
#include "Shader.h"

#include <string>
#include <vector>

namespace Entropy
{
	namespace Graphics
	{
		struct __declspec(dllexport) FaceIndex
		{
			unsigned int Position;
			unsigned int Normal;
			unsigned int TexCoord;
		};

		struct __declspec(dllexport) Vertex
		{
			Math::Vec3 Position;
			Math::Vec3 Normal;
			Math::Vec2 TexCoord;

			Vertex(Math::Vec3 position, Math::Vec3 normal = Math::Vec3(), Math::Vec2 texCoord = Math::Vec2()) : Position(position), Normal(normal), TexCoord(texCoord) {};
			Vertex(float x, float y, float z, float i = 0.0f, float j = 0.0f, float k = 0.0f, float tX = 0.0f, float tY = 0.0f) : Position(x, y, z), Normal(i, j, k), TexCoord(tX, tY) {};
		};

		class Mesh
		{
		private:
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			Material material;

		public:
			__declspec(dllexport) Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);

			void __declspec(dllexport) Draw(Shader& shader);
			void __declspec(dllexport) DrawInstanced(Shader& shader, unsigned int count);

			void __declspec(dllexport) setupInstancedMatrix();
		private:
			unsigned int VAO, VBO, EBO;
			
			void setupMesh();
		};

		class SkyboxMesh
		{
		private:
			std::vector<Vertex> vertices;
			unsigned int VAO, VBO;
			Texture texture;
		public:
			__declspec(dllexport) SkyboxMesh(Texture texture);
			void __declspec(dllexport) Draw(Shader& shader, Math::Mat4& view, Math::Mat4& projection);
		};
	}
}