#include "ofMain.h"
#include "SimpleDrawNode.h"

SimpleDrawNode::SimpleDrawNode(const ofVboMesh& vboMesh, const ofShader& shader, glm::vec3 color)
	: vboMesh {vboMesh}, shader {shader}, color {color}
{
}

void SimpleDrawNode::drawNode(const CameraMatrices& camera, const glm::mat4& model) const
{
	using namespace glm;

	mat4 mvp = mat4(camera.getProj() * camera.getView() * model);
	
	shader.begin();

	// Setup lighting parameters.
	shader.setUniform3f("lightDirection", normalize(vec3(-1, 1, 1)));
	shader.setUniform3f("lightColor", vec3(1, 1, 0.9));
	shader.setUniform3f("ambientColor", vec3(0.1));

	// Set up transforms.
	shader.setUniformMatrix4f("mvp", mvp);
	shader.setUniformMatrix3f("normalMatrix", glm::inverse(glm::transpose(model)));

	shader.setUniform3f("meshColor", color);

	vboMesh.draw();

	shader.end();
}