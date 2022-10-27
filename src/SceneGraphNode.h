#pragma once
#include "ofMain.h"
#include "CameraMatrices.h"
#include <list>
#include <memory>

struct SceneGraphNode
{
public:
	glm::mat4 transform{};

	std::list<std::shared_ptr<SceneGraphNode>> childNodes{};

	virtual ~SceneGraphNode() {};

	void drawSceneGraph(const CameraMatrices& camera, const glm::mat4& parentTransform = {})
	{
		// Get transform relative to parent transform.
		glm::mat4 model = parentTransform * transform;

		// Draw self.
		this->drawNode(camera, model);

		// Draw child nodes recursively (depth-first).
		for (const auto& node : this->childNodes)
		{
			node->drawSceneGraph(camera, model);
		}
	}

protected:
	virtual void drawNode(const CameraMatrices& camera, const glm::mat4& model) const
	{
		// Extend this class and override this draw function.
	}
};