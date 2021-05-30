#include "stdafx.h"
#include "../Include/DebugRenderSystem.h"

DebugRenderSystem::DebugRenderSystem(Registry& registry) : System(registry)
{
	RequireComponent<TransformComponent>();
	RequireComponent<BoxColliderComponent>();
}

void DebugRenderSystem::Update()
{
}

void DebugRenderSystem::Render(SDL_Renderer* renderer)
{
	for (Entity entity : m_systemEntities)
	{
		const TransformComponent entityTransform = m_registry.GetComponent<TransformComponent>(entity);
		const BoxColliderComponent entityBoxCollider = m_registry.GetComponent<BoxColliderComponent>(entity);

		SDL_Rect boxCollider = {
			static_cast<int>(entityTransform.position.x),
			static_cast<int>(entityTransform.position.y),
			static_cast<int>(entityBoxCollider.width * entityTransform.scale.x + entityBoxCollider.offset.x),
			static_cast<int>(entityBoxCollider.height * entityTransform.scale.y + entityBoxCollider.offset.y)
		};

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(renderer, &boxCollider);
	}
}
