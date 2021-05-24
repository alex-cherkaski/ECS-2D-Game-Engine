#pragma once
#include <SDL.h>

class Engine
{
public:
	static Engine& GetEngineInstance();
	~Engine();

	// Engine instance cannot be copied.
	Engine(const Engine& other) = delete;
	Engine& operator=(const Engine& other) = delete;

	// Engine instance cannot be moved.
	Engine(Engine&& other) = delete;
	Engine& operator=(Engine&& other) = delete;

	void Initialize();
	void Run();
	void Destroy();

private:
	Engine();

	void ProcessInput();
	void Update();
	void Render();

private:
	unsigned m_windowWidth;
	unsigned m_windowHeight;

	bool m_isRunning;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;


};

