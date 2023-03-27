#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <unordered_map>
#include <map>
#include <vector>
#include "3D/GameObject.h"
#include "../Math/CollisionHandler.h"
#include "../Rendering/Gui/GUIObject.h"
#include "../Graphics/ShaderHandler.h"
#include "Gui/GUIObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string tag_ = "");
	GameObject* GetGameObject(std::string tag_);

	void AddGUIObject(GUIObject* gui_, std::string tag_ = "");
	GUIObject* GetGUIObject(std::string tag_);


	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void Draw(Camera* camera_); 
private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::unordered_map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;
	static std::map<std::string, GUIObject*> GUIObjects;
};

#endif // !SCENEGRAPH_H