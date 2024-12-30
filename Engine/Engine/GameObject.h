#pragma once
//Serialization
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/access.hpp>
#include <memory>
//


#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include <string>
#include <vector>


class GameObject
{
public:

	//Serialization
	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(name),
			CEREAL_NVP(isActive),
			CEREAL_NVP(isEditing),
			CEREAL_NVP(components),
			CEREAL_NVP(children));
	}	
	//

	GameObject(const char* name, std::shared_ptr<GameObject> parent);
	virtual ~GameObject();

	void Update();

	void Enable();
	void Disable();

	std::shared_ptr<Component> AddComponent(std::shared_ptr<Component> component);
	std::shared_ptr<Component> GetComponent(ComponentType type);

public:
	std::shared_ptr<GameObject> parent;
	std::string name;

	std::shared_ptr<ComponentTransform> transform;
	std::shared_ptr<ComponentMesh> mesh;
	std::shared_ptr<ComponentMaterial> material;

	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<GameObject>> children;

	bool isActive = true;
	bool isEditing = false;
};