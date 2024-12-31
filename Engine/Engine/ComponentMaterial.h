#pragma once

#include "Component.h"
#include "Texture.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* gameObject);
	virtual ~ComponentMaterial();

	void Update() override;
	void OnEditor() override;

	void AddTexture(Texture* texture);

	json Serialize() const override;
	void Deserialize(const json& j) override;
public:
	Texture* materialTexture;
	GLuint textureId;

private:
	bool showCheckersTexture = false;
};