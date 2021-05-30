#pragma once
#include "ECS.h"

class DebugRenderSystem : public System
{
public:
	DebugRenderSystem(Registry& registry);

	void Update() override final;
	void Render(SDL_Renderer* renderer) override final;
};

