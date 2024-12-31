#pragma once

#include "Module.h"
#include "GameObject.h"
#include <nlohmann/json.hpp>
#include <iostream>

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
	void SaveScene(const std::string& filename);
	void LoadScene(const std::string& filename);
	//
public:
	GameObject* root = nullptr;
};