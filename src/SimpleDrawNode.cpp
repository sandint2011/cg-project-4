#include "ofMain.h"
#include "SimpleDrawNode.h"

SimpleDrawNode::SimpleDrawNode(const ofVboMesh& vboMesh, const ofShader& shader)
{
	this->vboMesh = vboMesh;
	this->shader = shader;
}

void SimpleDrawNode::drawNode(const CameraMatrices& camera, const glm::mat4& model)
{
	shader.begin();
	//mvp
	shader.setUniformMatrix3f("normalMatrix", glm::inverse(glm::transpose(model)));
	//mesh.draw(shader);
	shader.end();
}