#include "GameScene.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../../Engine/Rendering/Gui/GUIImageComponent.h"
#include "../../Engine/Audio/AudioHandler.h"
#include"../../Engine/Input/InputHandler.h"
#include"../../Engine/Math/CollisionHandler.h"

float yes{ 0.0f };
float no{ 0.0f };
GameObject* player;

GameScene::GameScene(){

}

GameScene::~GameScene(){
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	Engine::GetInstance()->SetCamera(new Camera());
	Engine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
	Engine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.5f, 0.1f, 0.1f, glm::vec3(1.0f, 1.0f, 1.0f)));
	AudioHandler::GetInstance()->Initialize(Engine::GetInstance()->GetCamera()->GetPosition(), glm::vec3(0), Engine::GetInstance()->GetCamera()->GetForward(), Engine::GetInstance()->GetCamera()->GetUp());
	InputHandler::GetInstance()->Initialize();
	physicsSolver = new PhysicsSolver();
	//emitter = new Emitter(100, "ParticleShader");

	//CollisionHandler::GetInstance()->OnCreate(100.0f);


	//TextureHandler::GetInstance()->CreateTexture("CheckerboardTexture", "Resources/Textures/CheckerboardTexture.png");

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	GameObject* appleObject = new GameObject(appleModel, glm::vec3(3.0f, 0.0f, 0.0f));
	GameObject* appleObject2 = new GameObject(appleModel, glm::vec3(-5.0f, 2.0f, 0.0f));
	//GameObject* diceObject = new GameObject(diceModel, glm::vec3(1.5f, 0.0f, 0.0f));

	player = appleObject;

	//SceneGraph::GetInstance()->AddGameObject(diceObject, "Dice");
	SceneGraph::GetInstance()->AddGameObject(appleObject, "Apple");
	SceneGraph::GetInstance()->AddGameObject(appleObject2, "Apple2");
	
	appleObject->AddComponent<AudioSource>("OOF.mp3", false, true, false);

	//Add a rigidbody component to the apple
	Rigidbody* rb = appleObject->AddComponent<Rigidbody>();
	physicsSolver->addObject(rb);

	rb->isKinematic = false;
	rb->mass = 2;

	rb = appleObject2->AddComponent<Rigidbody>();
	physicsSolver->addObject(rb);

	//rb = diceObject->AddComponent<Rigidbody>();
	//rb->isKinematic = false;
	//physicsSolver->addObject(rb);	

	//Create GUI Objects
	//GUIObject* object = new GUIObject(glm::vec2(900,150), glm::vec2(200,50));
	//object->AddComponent<GUIImageComponent>();
	//object->GetComponent<GUIImageComponent>()->OnCreate("WoodArrow", glm::vec2(0,0), glm::vec2(.4f,.2f),0, glm::vec4(1,1,1,1));

	//GUIObject* object2 = new GUIObject(glm::vec2(275, 150), glm::vec2(100, 50));
	//object2->AddComponent<GUIImageComponent>();
	//object2->GetComponent<GUIImageComponent>()->OnCreate("WoodArrow", glm::vec2(0, 0), glm::vec2(.4f, .2f), 0, glm::vec4(1, 1, 1, 1));
	
	//SceneGraph::GetInstance()->AddGUIObject(object, "GUI");
	//SceneGraph::GetInstance()->AddGUIObject(object2, "GUI");

	//object = nullptr;

	appleObject = nullptr;
	appleObject2 = nullptr;

	//delete diceModel;
	//delete appleModel;
	diceModel = nullptr;
	appleModel = nullptr;
	return true;
}

void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
	AudioHandler::GetInstance()->Update();
	InputHandler::GetInstance()->Update();
	//CollisionHandler::GetInstance()->Update(deltaTime_);
	physicsSolver->update(deltaTime_);
	//emitter->Update(deltaTime_);

	yes += deltaTime_;

	XINPUT_STATE xinput_state = InputHandler::GetInstance()->GetInputState();
	if (xinput_state.Gamepad.wButtons > 0 && yes > no) {
		switch (xinput_state.Gamepad.wButtons) {
		case XINPUT_GAMEPAD_A: {
				Model * appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
				GameObject* appleObject = new GameObject(appleModel, glm::vec3(3.0f, 2.0f, 0.0f));
				SceneGraph::GetInstance()->AddModel(appleModel);
				SceneGraph::GetInstance()->AddGameObject(appleObject);

				Rigidbody* rb = appleObject->AddComponent<Rigidbody>();
				physicsSolver->addObject(rb);

				glm::vec2 leftTrigger{ xinput_state.Gamepad.sThumbLX, xinput_state.Gamepad.sThumbLY };
				rb->Accelerate(glm::vec3(leftTrigger *= .2f, 0));

				no = yes + .5f;

				break;
			}
		case XINPUT_GAMEPAD_X:
			player->GetComponent<AudioSource>()->playSound(2);
			break;
		}
	}

	//Sticks L
	int16_t deadzone = 10000;
	int16_t xAxis = xinput_state.Gamepad.sThumbLX;
	int16_t yAxis = xinput_state.Gamepad.sThumbLY;
	if (xAxis > deadzone || xAxis < -deadzone || yAxis > deadzone || yAxis < -deadzone) {
		/// The thumb sticks return a signed two byte short 'short' range -32768 to 32767
		glm::vec2 leftTrigger{ xinput_state.Gamepad.sThumbLX, xinput_state.Gamepad.sThumbLY };
		player->GetComponent<Rigidbody>()->setVelocity(glm::vec3{ leftTrigger *= 0.0001f, 0 }, deltaTime_);
		//player->GetComponent<Rigidbody>()->Accelerate(glm::vec3{ leftTrigger, 0 } *= 0.01f);
	}
	else {
		player->GetComponent<Rigidbody>()->setVelocity(glm::vec3{ 0,0, 0 }, deltaTime_);
	}


}

void GameScene::Render(){
	SceneGraph::GetInstance()->Render(Engine::GetInstance()->GetCamera());
	//emitter->Render(Engine::GetInstance()->GetCamera());
}

void GameScene::Draw() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Draw(Engine::GetInstance()->GetCamera());// GUI Image Draw Function
}
