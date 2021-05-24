#pragma once
#include <glm.hpp>

struct TransformComponent
{
	glm::vec2 position;
	glm::vec2 velocity;
	float rotation;
	float scale;
};