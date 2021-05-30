#include "stdafx.h"
#include "../Include/Engine.h"
#include "../Include/Logger.h"
#include "../Include/Constants.h"

Engine& Engine::GetEngineInstance()
{
	static Engine engine;
	return engine;
}

Engine::~Engine()
{
	Destroy();
}

void Engine::Initialize()
{
	// Initialize all base SDL subsystems.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Log(SDL_GetError(), ERROR_LEVEL::ERROR);
		return;
	}

	// Create window.
	Uint32 windowFlags = SDL_WINDOW_BORDERLESS;
	m_window = SDL_CreateWindow(Constants::Window::WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::Window::WINDOW_WIDTH, Constants::Window::WINDOW_HEIGHT, windowFlags);
	if (m_window == nullptr)
	{
		Logger::Log(SDL_GetError(), ERROR_LEVEL::ERROR);
		return;
	}

	// Create renderer.
	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);
	if (m_renderer == nullptr)
	{
		Logger::Log(SDL_GetError(), ERROR_LEVEL::ERROR);
		return;
	}

	// Set OS video mode to full screen.
	//SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

	m_isRunning = true;
}

void Engine::LoadLevel(unsigned level)
{
	Entity entity = m_registry.CreateEntity();
	m_registry.AddComponent<TransformComponent>(entity, glm::vec2(0, 0), glm::vec2(0, 0), 0.0f);
}

void Engine::Run()
{
	while (m_isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Engine::Destroy()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

Engine::Engine() : m_windowWidth(0), m_windowHeight(0), m_isRunning(false), m_window(nullptr), m_renderer(nullptr), m_registry(Registry::GetRegistryInstance())
{
}

void Engine::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case (SDL_KEYDOWN):
			{
				// Escape key to close.
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					m_isRunning = false;
					break;
				}
			}

			// Pressing X button will close.
			case(SDL_QUIT):
			{
				m_isRunning = false;
				break;
			}

			default: break;
		}
	}
}

void Engine::Update()
{
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}
