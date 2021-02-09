#include "Engine/Core/Engine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	Engine::GetInstance()->SetGameInterface(new Game1);

	if (!Engine::GetInstance()->OnCreate("Game 258 Engine", 800, 600)) {
		Debug::Error("Engine failed to initialize", "Main.cpp", __LINE__);
		return 0;
	}
	Engine::GetInstance()->Run();
	return 0;
}