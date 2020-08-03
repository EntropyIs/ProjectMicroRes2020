#include "SpriteRenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Entropy/Math/Transform3D.h>
#include <Entropy/Math/Converters.h>

#include "ResourceManager.h"

using namespace Entropy;

SpriteRenderer::SpriteRenderer()
{
    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::Draw(Entropy::Math::Vec2 position, Entropy::Graphics::Texture& spriteSheet, Entropy::Math::Vec2 spriteIndex, SpriteData& spriteData, float rotAngle, Entropy::Math::Vec3 color)
{
    // Prepare Transformations
    Math::Mat4 model = Math::Translate(Math::Vec3(position.X - ((float)spriteData.cel_width / 2.0f), position.Y - ((float)spriteData.cel_height / 2.0f), 0.0f)) * Math::RotateZ(Math::Radians(rotAngle)) * Math::Scale((float)spriteData.cel_width, (float)spriteData.cel_height, 1.0f);

    ResourceManager::getShader("spriteShader").use();
    ResourceManager::getShader("spriteShader").setMat4("model", model);
    ResourceManager::getShader("spriteShader").setVec2("spriteOffset", spriteIndex);
    ResourceManager::getShader("spriteShader").setVec2("spriteSheetSize", Math::Vec2((float)spriteData.num_rows, (float)spriteData.num_cols));
    ResourceManager::getShader("spriteShader").setVec3("spriteColor", color);

    // Render Sprite
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, spriteSheet.ID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	unsigned int VBO;
    float vertices[] =
    {
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}
