#pragma once

#include "../../Math/Vec2.h"
#include "../../Math/Vec3.h"
#include "../Mesh.h"

#include <vector>
#include <string>

namespace Entropy
{
	namespace Graphics
	{
		class WavefrontObj
		{
		private:
			struct FaceIndex {
				unsigned int vertexPosition;
				unsigned int vertexNormal;
				unsigned int vertexTextureCoord;
				FaceIndex() :vertexPosition(0), vertexNormal(0), vertexTextureCoord(0) {};
			};

			struct ObjectData {
				std::string objectName;
				std::vector<Math::Vec3> vertexPositions;
				std::vector<Math::Vec3> vertexNormals;
				std::vector<Math::Vec2> vertexTextureCoords;
				std::vector<FaceIndex> faceIndices;
				std::string materialName;
				ObjectData(std::string objectName);
			};

			std::vector<ObjectData> objects;
			std::vector<Material> materials;

			std::vector<std::string> mtlFiles;

			std::string directory;

			void pharseVertexPosition(std::vector<std::string> lineData, unsigned int index);
			void pharseTextureCoord(std::vector<std::string> lineData, unsigned int index);
			void pharseNormal(std::vector<std::string> lineData, unsigned int index);
			void pharseFace(std::vector<std::string> lineData, unsigned int index, unsigned int positionOffset, unsigned int textureCoordOffset, unsigned int normalOffset);

			unsigned int addObject(std::string objectName);
			unsigned int getObjectIndex(std::string objectName);
			bool hasObject(std::string objectName);

			void pharseColorAmbient(std::vector<std::string> lineData, unsigned int index);
			void pharseColorDiffuse(std::vector<std::string> lineData, unsigned int index);
			void pharseColorSpecular(std::vector<std::string> lineData, unsigned int index);
			void pharseShininess(std::vector<std::string> lineData, unsigned int index);
			void pharseTexture(std::vector<std::string> lineData, unsigned int index);

			unsigned int addMaterial(std::string materialName);
			unsigned int getMaterialIndex(std::string materialName);
			bool hasMaterial(std::string materialName);

			bool readObjFile(const char* path);
			bool readMtlFile(const char* path);

		public:
			__declspec(dllexport) WavefrontObj(std::string path);

			std::vector<Mesh> __declspec(dllexport) getAll();

			Mesh __declspec(dllexport) getMesh(const char* objectName);
			Mesh __declspec(dllexport) getMesh(unsigned int index);

			std::vector<Vertex> __declspec(dllexport) getVertices(const char* objectName);
			std::vector<Vertex> __declspec(dllexport) getVertices(unsigned int index);

			std::vector<unsigned int> __declspec(dllexport) getIndices(const char* objectName);
			std::vector<unsigned int> __declspec(dllexport) getIndices(unsigned int index);

			Material __declspec(dllexport) getMaterial(const char* objectName);
			Material __declspec(dllexport) getMaterial(unsigned int index);

		};
	}
}