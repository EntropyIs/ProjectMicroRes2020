#pragma once

#include <vector>
#include <string>

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

		class LoadTexture
		{
		private:
			static Image LoadBitmap(std::string path);
			static Image LoadJPEG(std::string path);
			static Image LoadGif(std::string path);
			static Image LoadTiff(std::string path);
			static Image LoadPNG(std::string path);
		public:
			static __declspec(dllexport) Texture LoadFromFile(std::string path, std::string type);
			static __declspec(dllexport) Texture LoadFromImageFile(std::string path, std::string type, bool interpolate = true);

			static __declspec(dllexport) Texture LoadCubeMap(std::vector<std::string> paths);
		};
	}
}