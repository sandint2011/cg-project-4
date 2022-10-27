#pragma once
#include "SceneGraphNode.h"
#include "ofMain.h"

class SimpleDrawNode : public SceneGraphNode
{
public:
	SimpleDrawNode(const ofVboMesh& vboMesh, const ofShader& shader, const glm::vec3 color);

protected:
	// Override.
	void drawNode(const CameraMatrices& camera, const glm::mat4& model) const override;

private:
	const ofVboMesh& vboMesh;
	const ofShader& shader;
	const glm::vec3 color;
};