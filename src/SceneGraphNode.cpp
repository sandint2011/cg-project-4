#pragma once
#include "ofMain.h"
#include "CameraMatrices.h""
#include <list>

struct SceneGraphNode
{
public:
	glm::mat4 transform;

	std::list<std::shared_ptr<SceneGraphNode>> childNodes;

	virtual ~SceneGraphNode() {};

	void drawSceneGraph(const CameraMatrices &camera, const glm::mat4& globalTransform);

protected:
	virtual void drawNode(const CameraMatrices &camera, const glm::mat4 &model);
};