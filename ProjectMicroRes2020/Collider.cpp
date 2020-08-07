#include "Collider.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Entropy/Math/Transform3D.h>

#include "ResourceManager.h"

Entropy::Math::Vec2& BoxCollider::getPosition()
{
	return position;
}

void BoxCollider::setPosition(Entropy::Math::Vec2 position)
{
    this->position = position;
}

void BoxCollider::setPosition(float x, float y)
{
    position = Entropy::Math::Vec2(x, y);
}

const bool BoxCollider::detect(const BoxCollider& other) const
{
	Entropy::Math::Vec2 otherlower = other.position - other.offset;
	Entropy::Math::Vec2 otherUpper = otherlower + other.size;
	Entropy::Math::Vec2 lower = position - offset;
	Entropy::Math::Vec2 upper = lower + size;

	return (lower.X < otherUpper.X&& upper.X > otherlower.X &&
		lower.Y < otherUpper.Y&& upper.Y > otherlower.Y);
}

#ifdef _ShowCollider
void BoxCollider::initRendererData()
{
    Entropy::Math::Vec2 lower = Entropy::Math::Vec2() - offset;
    Entropy::Math::Vec2 upper = lower + size;

    unsigned int VBO;
    float vertices[] =
    {
        lower.X, upper.Y,
        upper.X, lower.Y,
        lower.X, lower.Y,

        lower.X, upper.Y,
        upper.X, upper.Y,
        upper.X, lower.Y
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void BoxCollider::draw()
{
    Entropy::Math::Mat4 model = Entropy::Math::Translate(Entropy::Math::Vec3(position.X, position.Y));
    Entropy::Graphics::Shader shader = ResourceManager::getShader("hitboxShader");
    shader.setMat4("Model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
#endif // _ShowCollider2