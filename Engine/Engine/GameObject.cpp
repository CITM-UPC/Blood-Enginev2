#include "GameObject.h"

GameObject::GameObject(const char* name, GameObject* parent) : parent(parent), name(name)
{
	transform = new ComponentTransform(this);
	mesh = new ComponentMesh(this);
	material = new ComponentMaterial(this);

	AddComponent(transform);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (isActive)
	{
		for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
		{
			(*it)->Update();
		}
		for (std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			(*it)->Update();
		}
	}
}

void GameObject::Enable()
{
}
void GameObject::Disable()
{
}

Component* GameObject::AddComponent(Component* component)
{
	components.push_back(component);

	return component;
}
//SERGIO
json GameObject::Serialize() const
{
    json j;
    j["name"] = name;
    j["isActive"] = isActive;
    j["components"] = json::array();
    for (const auto& component : components)
    {
        j["components"].push_back(component->Serialize());
    }
    j["children"] = json::array();
    for (const auto& child : children)
    {
        j["children"].push_back(child->Serialize());
    }
    return j;
}

void GameObject::Deserialize(const json& j)
{
	name = j["name"];
	isActive = j["isActive"];
	isEditing = j["isEditing"];

	// Deserialize components
	for (const auto& componentData : j["components"])
	{
		ComponentType type = componentData["type"];
		Component* component = nullptr;

		switch (type)
		{
		case ComponentType::TRANSFORM:
			component = new ComponentTransform(this);
			break;
		case ComponentType::MESH:
			component = new ComponentMesh(this);
			break;
		case ComponentType::MATERIAL:
			component = new ComponentMaterial(this);
			break;
		default:
			break;
		}

		if (component)
		{
			component->Deserialize(componentData);
			AddComponent(component);
		}
	}

	// Deserialize children
	for (const auto& childData : j["children"])
	{
		GameObject* child = new GameObject("", this);
		child->Deserialize(childData);
		children.push_back(child);
	}
}

//
Component* GameObject::GetComponent(ComponentType type)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if ((*it)->type == type) {
			return (*it);
		}
	}

	return nullptr;
}