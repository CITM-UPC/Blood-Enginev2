#pragma once

#include "Module.h"
#include "GameObject.h"
#include <fstream>

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
	//SERGIO
	void SaveScene(const std::string& filePath);
	void LoadScene(const std::string& filePath);
	//
public:
	GameObject* root = nullptr;
};