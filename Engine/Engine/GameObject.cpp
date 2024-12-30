#include "GameObject.h"

GameObject::GameObject(const char* name, std::shared_ptr<GameObject> parent)
    : parent(parent), name(name)
{
    transform = std::make_shared<ComponentTransform>(this);
    mesh = std::make_shared<ComponentMesh>(this);
    material = std::make_shared<ComponentMaterial>(this);

    AddComponent(transform);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
    if (isActive)
    {
        for (auto& component : components)
        {
            component->Update();
        }
        for (auto& child : children)
        {
            child->Update();
        }
    }
}

void GameObject::Enable()
{
    isActive = true;
}

void GameObject::Disable()
{
    isActive = false;
}

std::shared_ptr<Component> GameObject::AddComponent(std::shared_ptr<Component> component)
{
    components.push_back(component);
    return component;
}

std::shared_ptr<Component> GameObject::GetComponent(ComponentType type)
{
    for (auto& component : components)
    {
        if (component->type == type)
        {
            return component;
        }
    }
    return nullptr;
}
