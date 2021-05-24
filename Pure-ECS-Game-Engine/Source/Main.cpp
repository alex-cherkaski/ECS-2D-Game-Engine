#include "../Include/Engine.h"

int main(int argc, char* argv[])
{
	Engine& engine = Engine::GetEngineInstance();

	engine.Initialize();
	engine.Run();
	engine.Destroy();

	return 0;
}