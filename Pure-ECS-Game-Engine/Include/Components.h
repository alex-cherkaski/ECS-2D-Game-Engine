#pragma once
#include <glm.hpp>

struct TransformComponent
{
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

	TransformComponent(const glm::vec2& position, const glm::vec2& scale, float rotation): 
		position(position), scale(scale), rotation(rotation) {}
};

struct BoxColliderComponent
{
	glm::vec2 offset;
	float width;
	float height;

	BoxColliderComponent(const glm::vec2& offset, float width, float height) :
		offset(offset), width(width), height(height) {}
};