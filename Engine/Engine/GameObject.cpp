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
    for (const auto& componentJson : j["components"])
    {
        ComponentType type = static_cast<ComponentType>(componentJson["type"]);
        Component* component = GetComponent(type);
        if (component)
        {
            component->Deserialize(componentJson);
        }
    }
    for (const auto& childJson : j["children"])
    {
        std::string childName = childJson["name"];
        GameObject* child = new GameObject(childName.c_str(), this);
        child->Deserialize(childJson);
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