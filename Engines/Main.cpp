#include "Engine/Core/Engine.h"

int main(int argc, char* argv[]) {

	if (!Engine::GetInstance()->OnCreate("Game 258 Engine", 800, 600)) {
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}
	Engine::GetInstance()->Run();
	return 0;
}