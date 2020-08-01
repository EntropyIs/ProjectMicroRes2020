#pragma once

#include "../Math/Vec3.h"
#include "Model/Image.h"

#include <vector>
#include <string>

namespace Entropy
{
	namespace Graphics
	{
		struct Material
		{
			std::string Name;
			Math::Vec3 Ambient;
			Math::Vec3 Diffuse;
			Math::Vec3 Specular;
			float Shininess;
			float Transparancy;
			std::vector<Texture> Textures;

			// Default
			Material(std::string name) : Name(name), Ambient(0.2f), Diffuse(0.8f), Specular(1.0f), Shininess(0.5f), Transparancy(1.0f) {};
			// Shininess
			Material(std::string name, float shininess) : Name(name), Ambient(0.2f), Diffuse(0.8f), Specular(1.0f), Shininess(shininess), Transparancy(1.0f) {}
			// Shininess + Color
			Material(std::string name, float shininess, float r, float g, float b) : Name(name), Ambient(0.2f * r, 0.2f * g, 0.2f * b), Diffuse(0.8f * r, 0.8f * g, 0.8f * b), Specular(r, g, b), Shininess(shininess), Transparancy(1.0f) {}
			Material(std::string name, float shininess, Math::Vec3 color) : Name(name), Ambient(0.2f * color), Diffuse(0.8f * color), Specular(color), Shininess(shininess), Transparancy(1.0f) {}
			// Shininess + Ambient + Diffuse + Specular
			Material(std::string name, float shininess, float aR, float aG, float aB, float dR, float dG, float dB, float sR, float sG, float sB) : Name(name), Ambient(aR, aG, aB), Diffuse(dR, dG, dB), Specular(sR, sG, sB), Shininess(shininess), Transparancy(1.0f) {}
			Material(std::string name, float shininess, Math::Vec3 ambient, Math::Vec3 diffuse, Math::Vec3 specular) : Name(name), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess), Transparancy(1.0f) {}
		};

		namespace Materials
		{
			static Material Emerald = Material("Emerald", 0.6f, 0.0215f, 0.1745f, 0.0215f, 0.07568f, 0.61424f, 0.07568f, 0.633f, 0.727811f, 0.633f);
			static Material Jade = Material("Jade", 0.1f, 0.135f, 0.2225f, 0.1575f, 0.54f, 0.89f, 0.63f, 0.316228f, 0.316228f, 0.316228f);
			static Material Obsidian = Material("Obsidian", 0.3f, 0.05375f, 0.05f, 0.06625f, 0.18275f, 0.17f, 0.22525f, 0.332741f, 0.328634f, 0.346435f);
			static Material Pearl = Material("Pearl", 0.088f, 0.25f, 0.20725f, 0.20725f, 1.0f, 0.829f, 0.829f, 0.296648f, 0.296648f, 0.296648f);
			static Material Ruby = Material("Ruby", 0.6f, 0.1745f, 0.01175f, 0.01175f, 0.61424f, 0.04136f, 0.04136f, 0.727811f, 0.626959f, 0.626959f);
			static Material Turquoise = Material("Turquoise", 0.1f, 0.1f, 0.18725f, 0.1745f, 0.396f, 0.74151f, 0.69102f, 0.297254f, 0.30829f, 0.306678f);
			static Material Brass = Material("Brass", 0.21794872f, 0.329412f, 0.223529f, 0.027451f, 0.780392f, 0.568627f, 0.113725f, 0.992157f, 0.941176f, 0.807843f);
			static Material Bronze = Material("Bronze", 0.2f, 0.2125f, 0.1275f, 0.054f, 0.714f, 0.4284f, 0.18144f, 0.393548f, 0.271906f, 0.166721f);
			static Material Chrome = Material("Chrome", 0.6f, 0.25f, 0.25f, 0.25f, 0.4f, 0.4f, 0.4f, 0.774597f, 0.774597f, 0.774597f);
			static Material Copper = Material("Copper", 0.1f, 0.19125f, 0.0735f, 0.0225f, 0.7038f, 0.27048f, 0.0828f, 0.256777f, 0.137622f, 0.086014f);
			static Material Gold = Material("Gold", 0.4f, 0.24725f, 0.1995f, 0.0745f, 0.75164f, 0.60648f, 0.22648f, 0.628281f, 0.555802f, 0.366065f);
			static Material Silver = Material("Silver", 0.4f, 0.19225f, 0.19225f, 0.19225f, 0.50754f, 0.50754f, 0.50754f, 0.508273f, 0.508273f, 0.508273f);
			static Material BlackPlastic = Material("BlackPlastic", 0.25f, 0.0f, 0.0f, 0.0f, 0.01f, 0.01f, 0.01f, 0.5f, 0.5f, 0.5f);
			static Material CyanPlastic = Material("CyanPlastic", 0.25f, 0.0f, 0.1f, 0.06f, 0.0f, 0.50980392f, 0.50980392f, 0.50196078f, 0.50196078f, 0.50196078f);
			static Material GreenPlastic = Material("GreenPlastic", 0.25f, 0.0f, 0.0f, 0.0f, 0.1f, 0.35f, 0.1f, 0.45f, 0.55f, 0.45f);
			static Material RedPlastic = Material("RedPlastic", 0.25f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.7f, 0.6f, 0.6f);
			static Material WhitePlastic = Material("WhitePlastic", 0.25f, 0.0f, 0.0f, 0.0f, 0.55f, 0.55f, 0.55f, 0.7f, 0.7f, 0.7f);
			static Material YellowPlastic = Material("YellowPlastic", 0.25f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.6f, 0.6f, 0.5f);
			static Material BlackRubber = Material("BlackRubber", 0.078125f, 0.02f, 0.02f, 0.02f, 0.01f, 0.01f, 0.01f, 0.4f, 0.4f, 0.4f);
			static Material CyanRubber = Material("CyanRubber", 0.078125f, 0.0f, 0.05f, 0.05f, 0.4f, 0.5f, 0.5f, 0.04f, 0.7f, 0.7f);
			static Material GreenRubber = Material("GreenRubber", 0.078125f, 0.0f, 0.05f, 0.0f, 0.4f, 0.5f, 0.4f, 0.04f, 0.7f, 0.04f);
			static Material RedRubber = Material("RedRubber", 0.078125f, 0.05f, 0.0f, 0.0f, 0.5f, 0.4f, 0.4f, 0.7f, 0.04f, 0.04f);
			static Material WhiteRubber = Material("WhiteRubber", 0.078125f, 0.05f, 0.05f, 0.05f, 0.5f, 0.5f, 0.5f, 0.7f, 0.7f, 0.7f);
			static Material YellowRubber = Material("YellowRubber", 0.078125f, 0.05f, 0.05f, 0.0f, 0.5f, 0.5f, 0.4f, 0.7f, 0.7f, 0.04f);
		}
	}
}