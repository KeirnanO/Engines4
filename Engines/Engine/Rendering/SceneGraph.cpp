#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::unordered_map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::unordered_map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GUIObject*> SceneGraph::GUIObjects = std::map<std::string, GUIObject*>();


SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph(){
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance(){
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy(){
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_){
	GLuint shader = model_->GetShaderProgram();
	if (sceneModels.find(shader) == sceneModels.end()) {
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(shader, std::vector<Model*>()));
	}
	sceneModels[shader].push_back(model_);
}


void SceneGraph::AddGameObject(GameObject* go_, std::string tag_){
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else {
		Debug::Error("Trying to add a GameObject with a tag " + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}

	//CollisionHandler::GetInstance()->AddObject(go_);
}

void SceneGraph::AddGUIObject(GUIObject* gui_, std::string tag_) {
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(GUIObjects.size() + 1);
		gui_->SetTag(newTag);
		GUIObjects[newTag] = gui_;
	}
	else if (GUIObjects.find(tag_) == GUIObjects.end()) {
		gui_->SetTag(tag_);
		GUIObjects[tag_] = gui_;
	}
	else {
		Debug::Error("Trying to add a GuiObject with a tag " + tag_ +
			" that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GuiObject" + std::to_string(GUIObjects.size() + 1);
		gui_->SetTag(newTag);
		GUIObjects[newTag] = gui_;
	}
}


GameObject* SceneGraph::GetGameObject(std::string tag_) {
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

GUIObject* SceneGraph::GetGUIObject(std::string tag_) {
	if (GUIObjects.find(tag_) != GUIObjects.end()) {
		return GUIObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_){
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_){
	for (auto go : sceneGameObjects) {
		go.second->Render(camera_);
	}
}

void SceneGraph::Draw(Camera* camera_) {

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(ShaderHandler::GetInstance()->GetShader("GUIShader"));

	for (auto m : GUIObjects) {
		m.second->Draw(camera_);
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

}


