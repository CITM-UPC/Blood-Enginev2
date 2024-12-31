#pragma once

#include "Component.h"
#include "Mesh.h"

class Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* gameObject);
	virtual ~ComponentMesh();

	void Update() override;
	void OnEditor() override;

	json Serialize() const override;
	void Deserialize(const json& j) override;
public:
	Mesh* mesh;

private:
	bool showVertexNormals = false;
	bool showFaceNormals = false;
};