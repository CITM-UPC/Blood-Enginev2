#pragma once
//Serialization
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <cereal/archives/json.hpp>
//


#include "Module.h"
#include "GameObject.h"

class GameObject;

class ModuleScene : public Module
{
public:
	ModuleScene(App* app);
	virtual ~ModuleScene();

	bool Awake();
	bool Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(const char* name, GameObject* parent);
	//Serialization
	bool SaveScene(const char* filePath);
	bool LoadScene(const char* filePath);
	//
public:
	GameObject* root = nullptr;
};