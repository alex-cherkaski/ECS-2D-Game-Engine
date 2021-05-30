#include "stdafx.h"
#include "../Include/Engine.h"

int main(int argc, char* argv[])
{
	Engine& engine = Engine::GetEngineInstance();

	engine.Initialize();
	engine.LoadLevel(0);
	engine.Run();
	engine.Destroy();

	return 0;
}