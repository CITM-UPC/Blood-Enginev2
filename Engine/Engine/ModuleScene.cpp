#include "ModuleScene.h"
#include "App.h"

ModuleScene::ModuleScene(App* app) : Module(app), root(nullptr)
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Awake()
{
	root = CreateGameObject("Untitled Scene", nullptr);

	return true;
}

bool ModuleScene::Update(float dt)
{
	root->Update();

	return true;
}

bool ModuleScene::CleanUp()
{
	LOG(LogType::LOG_INFO, "Cleaning ModuleScene");

	return true;
}


void ModuleScene::SaveScene(const std::string& filePath)
{
    json sceneJson = root->Serialize();
    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << sceneJson.dump(4);
        file.close();
    }
}

void ModuleScene::LoadScene(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (file.is_open())
    {
        json sceneJson;
        file >> sceneJson;
        file.close();
        root->Deserialize(sceneJson);
    }
}

GameObject* ModuleScene::CreateGameObject(const char* name, GameObject* parent)
{
	GameObject* gameObject = new GameObject(name, parent);

	if (parent != nullptr) parent->children.push_back(gameObject);

	return gameObject;
}