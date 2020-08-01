#pragma once

#include "Shader.h"
#include "Mesh.h"

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Entropy
{
	namespace Graphics
	{
		class Model
		{
		private:
			std::vector<Mesh> meshes;

		public:
			__declspec(dllexport) Model(const char* path);
			__declspec(dllexport) Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);

			void __declspec(dllexport) setupInstancedMatrix();

			void __declspec(dllexport) Draw(Shader& shader);
			void __declspec(dllexport) DrawInstanced(Shader& shader, unsigned int count);
		};
	}
}
