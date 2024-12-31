#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

class GameObject;

enum class ComponentType
{
	NONE,
	TRANSFORM,
	MESH,
	MATERIAL,
};

class Component
{
public:
	Component(GameObject* owner, ComponentType type);
	virtual ~Component();

	virtual void Update();
	virtual void OnEditor();

	void Enable();
	void Disable();

	virtual json Serialize() const = 0;
	virtual void Deserialize(const json& j) = 0;

public:
	bool active;
	GameObject* gameObject;
	ComponentType type;
};