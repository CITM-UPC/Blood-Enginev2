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


void ModuleScene::SaveScene(const std::string& filename)
{
    json sceneJson = root->Serialize();
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << sceneJson.dump(4);
        file.close();
    }
}

void ModuleScene::LoadScene(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        try
        {
            json sceneJson;
            file >> sceneJson;
            file.close();
            root->Deserialize(sceneJson);
        }
        catch (const json::parse_error& e)
        {
            std::cerr << "Error de parseo en el archivo JSON: " << e.what() << std::endl;
        }
        catch (const json::type_error& e)
        {
            std::cerr << "Error de tipo en el archivo JSON: " << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error al cargar la escena: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "No se pudo abrir el archivo para leer: " << filename << std::endl;
    }
}

GameObject* ModuleScene::CreateGameObject(const char* name, GameObject* parent)
{
	GameObject* gameObject = new GameObject(name, parent);

	if (parent != nullptr) parent->children.push_back(gameObject);

	return gameObject;
}