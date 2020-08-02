#include "SpriteRenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Entropy/Math/Transform3D.h>
#include <Entropy/Math/Converters.h>

using namespace Entropy;

SpriteRenderer::SpriteRenderer()
{
    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::Draw(Graphics::Shader& shader, Math::Vec2 position, Graphics::Texture& spriteSheet, Math::Vec2 spriteIndex, Math::Vec2 spriteSheetSize, unsigned int spriteWidth, unsigned int spriteHeight, float rotAngle, Math::Vec3 color)
{
    // Prepare Transformations
    Math::Mat4 model = Math::Translate(Math::Vec3(position.X - (spriteWidth/2.0f), position.Y - (spriteHeight/2.0f), 0.0f)) * Math::RotateZ(Math::Radians(rotAngle)) * Math::Scale(spriteWidth, spriteHeight, 1.0f);

    shader.use();
    shader.setMat4("model", model);
    shader.setVec2("spriteOffset", spriteIndex + Math::Vec2(1.0f));
    shader.setVec2("spriteSheetSize", spriteSheetSize);
    shader.setVec3("spriteColor", color);

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
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
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
