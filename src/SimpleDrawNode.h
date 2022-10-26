#pragma once
#include "SceneGraphNode.h"
#include "ofMain.h"

class SimpleDrawNode : public SceneGraphNode
{
public:
	SimpleDrawNode(const ofVboMesh& vboMesh, const ofShader& shader);

protected:
	virtual void drawNode(const CameraMatrices& camera, const glm::mat4& model);

private:
	ofVboMesh& vboMesh;
	ofShader& shader;
};