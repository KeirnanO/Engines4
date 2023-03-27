#include "Engine/Core/Engine.h"
#include "Game/Game1.h"
#include "Resources/rapidxml.hpp"

int main(int argc, char* args[]) {
	
	

	//Start Engine
	Engine::GetInstance()->SetGameInterface(new Game1);

	if (!Engine::GetInstance()->OnCreate("Game 258 Engine", 1200, 900)) {
		Debug::Error("Engine failed to initialize", "Main.cpp", __LINE__);
		return 0;
	}
	Engine::GetInstance()->Run();

	return 0;
}

void ReadXMLFile() {
	std::cout << "\n\n XML FILE \n\n" << std::endl;

	std::ifstream file("./Engine/Engine.xml");
	rapidxml::xml_document <> doc;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node <>* root = doc.first_node("group");
	std::string gameTitle = root->first_node("gametitle")->value();
	std::string engine = root->first_node("engine")->value();

	std::cout << gameTitle << std::endl;
	std::cout << engine << std::endl;

	for (rapidxml::xml_node <>* personNode = root->first_node("people")->first_node("person"); ; personNode = personNode->next_sibling()) {
		std::string title = personNode->first_node("title")->value();
		std::string given = personNode->first_node("given")->value();
		std::string family = personNode->first_node("family")->value();

		std::cout << given << " " << family << ": " << title << std::endl;
	}

	std::string description = root->first_node("description")->value();

	std::cout << description << std::endl;


	std::string start;

	std::cin >> start;
}