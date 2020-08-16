#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Entropy
{
	namespace Graphics
	{
		struct Image
		{
			unsigned int width;
			unsigned int height;
			std::vector<char> data;
		};

		struct Texture
		{
			unsigned int ID;
			std::string Type;

			Texture(unsigned int id, std::string type) : ID(id), Type(type) {};
			Texture() : ID(0), Type() {};
		};

		class __declspec(dllexport) LoadTexture
		{
		private:
			static Image LoadBitmap(std::string path);
			static Image LoadJPEG(std::string path);
			static Image LoadGif(std::string path);
			static Image LoadTiff(std::string path);
			static Image LoadPNG(std::string path);
		public:
			static GLFWimage LoadImage(std::string path);

			static Texture LoadFromFile(std::string path, std::string type);
			static Texture LoadFromImageFile(std::string path, std::string type, bool interpolate = true);
			
			static Texture LoadCubeMap(std::vector<std::string> paths);
		};
	}
}