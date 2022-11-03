#include "ofApp.h"
#include <vector>
#include <random>
#include "SimpleDrawNode.h"
#include "SimpleAnimationNode.h"
#include "CameraMatrices.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();

	ofEnableDepthTest();
	glEnable(GL_CULL_FACE);

	//ofSetBackgroundColor(135, 205, 235, 255);

	// Load mesh and invert its normals.
	cylanderMesh.load("cylinder.ply");
	cylanderMesh.flatNormals();
	for (int i = 0; i < cylanderMesh.getNumNormals(); i++)
	{
		cylanderMesh.setNormal(i, -cylanderMesh.getNormal(i));
	}


	sphereMesh.load("sphere.ply");
	sphereMesh.flatNormals();
	for (int i = 0; i < sphereMesh.getNumNormals(); i++)
	{
		sphereMesh.setNormal(i, -sphereMesh.getNormal(i));
	}

	cubeMesh.load("cube.ply");
	cubeMesh.flatNormals();
	for (int i = 0; i < cubeMesh.getNumNormals(); i++)
	{
		cubeMesh.setNormal(i, -cubeMesh.getNormal(i));
	}

	// Adds the body to the scene
	root.childNodes.emplace_back(new SimpleDrawNode(cylanderMesh, shader));
	root.childNodes.back()->localTransform = glm::rotate(glm::radians(-25.0f), glm::vec3(1, 0, 0));
	bodyMeshNode = root.childNodes.back();

	//makes the head
	bodyMeshNode->childNodes.emplace_back(new SimpleAnimationNode(10.0f,glm::vec3(1,0,0)));
	bodyMeshNode->childNodes.back()->localTransform = glm::translate(glm::vec3(0,1,0));
	headMeshNode = bodyMeshNode->childNodes.back();




	//make the left shoulder
	bodyMeshNode->childNodes.emplace_back(new SimpleDrawNode(cylanderMesh, shader));
	bodyMeshNode->childNodes.back()->localTransform = glm::translate(glm::vec3(-1.1, .5, 0)) * glm::rotate(glm::radians(90.0f), glm::vec3(0, 0, 1))  * glm::scale(glm::vec3(.3,.1,.3));
	shoulderLeftNode = bodyMeshNode->childNodes.back();

	// make the right shoulder
	bodyMeshNode->childNodes.emplace_back(new SimpleDrawNode(cylanderMesh, shader));
	bodyMeshNode->childNodes.back()->localTransform = glm::translate(glm::vec3(1.1, .5, 0)) * glm::rotate(glm::radians(-90.0f), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(.3, .1, .3));
	shoulderRightNode = bodyMeshNode->childNodes.back();


	shoulderLeftNode->childNodes.emplace_back(new SimpleDrawNode(cubeMesh, shader));
	shoulderLeftNode->childNodes.back()->localTransform = glm::translate(glm::vec3(-2.5, 0, 0)) * glm::scale(glm::vec3(2.5, 1, .75));
	leftArmNode = shoulderLeftNode->childNodes.back();

	reloadShaders();
}

//--------------------------------------------------------------
void ofApp::reloadShaders()
{
	if (needsShaderReload)
	{
		// Reload all shaders here.
		shader.load("shader.vert", "shader.frag");

		needsShaderReload = false;
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	reloadShaders();

	using namespace glm;

	camera.position += mat3(rotate(cameraHead, vec3(0, 1, 0))) * velocity * ofGetLastFrameTime();
	camera.rotation = (rotate(cameraHead, vec3(0, 1, 0)) * rotate(cameraPitch, vec3(1, 0, 0)));


}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;
	
	// Camera settings.
	const float nearClip = 0.1;
	const float farClip = 200;
	float aspectRatio = static_cast<float>(ofGetViewportWidth()) / static_cast<float>(ofGetViewportHeight());

	// Calculate view and projection matrices for camera.
	CameraMatrices cameraMatrices{ camera, aspectRatio, nearClip, farClip };

	// Draw the whole scene graph, starting with the root and recursively drawing its children.
	root.drawSceneGraph(cameraMatrices);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	
}

//--------------------------------------------------------------
void ofApp::updateCameraRotation(float dx, float dy)
{
	using namespace glm;
	cameraPitch -= dy;
	cameraPitch = clamp(cameraPitch, radians(-89.0f), radians(89.0f));
	cameraHead -= dx;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	using namespace glm;

	if (key == '`')
	{
		needsShaderReload = true;
	}

	const float cameraSpeed = 20;
	const float sprint = 5;
	const float dt = ofGetLastFrameTime();

	//// Forward / backward.
	//if (key == 'w')
	//	camera.position += cameraFront * cameraSpeed * dt;
	//else if (key == 'W')
	//	camera.position += cameraFront * cameraSpeed * sprint * dt;
	//if (key == 's')
	//	camera.position -= cameraFront * cameraSpeed * dt;
	//else if (key == 'S')
	//	camera.position -= cameraFront * cameraSpeed * sprint * dt;

	//// Left / right.
	//if (key == 'a')
	//	camera.position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
	//else if (key == 'A')
	//	camera.position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * sprint * dt;
	//if (key == 'd')
	//	camera.position += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
	//else if (key == 'D')
	//	camera.position += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * sprint * dt;

	//// Up / down.
	//if (key == 'q')
	//	camera.position += cameraUp * cameraSpeed * dt;
	//else if (key == 'Q')
	//	camera.position += cameraUp * cameraSpeed * sprint * dt;
	//if (key == 'e')
	//	camera.position -= cameraUp * cameraSpeed * dt;
	//else if (key == 'E')
	//	camera.position -= cameraUp * cameraSpeed * sprint * dt;

	// Move along the x axis.
	if (key == 'x')
		camera.position.x += cameraSpeed * dt;
	else if (key == 'X')
		camera.position.x -= cameraSpeed * dt;

	// Move along the y axis.
	if (key == 'y')
		camera.position.y += cameraSpeed * dt;
	else if (key == 'Y')
		camera.position.y -= cameraSpeed * dt;

	// Move along z axis.
	if (key == 'z')
		camera.position.z += cameraSpeed * dt;
	else if (key == 'Z')
		camera.position.z -= cameraSpeed * dt;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	// Get the mouse's change ins position since last frame.
	float dx = (x - prevMouseX);
	float dy = (y - prevMouseY);
	prevMouseX = x;
	prevMouseY = y;

	// Calculate camera direction.
	cameraDirection;
	cameraDirection.x = cos(cameraHead - glm::radians(90.0f)) * cos(cameraPitch); // Sutract 90 degrees from head because otherwise 0 radians points at +X instead of -Z like we want.
	cameraDirection.y = -sin(cameraPitch); // Negative because otherwise we're doing inverted Y and that's gross.
	cameraDirection.z = sin(cameraHead - glm::radians(90.0f)) * cos(cameraPitch); // Sutract 90 degrees from head because otherwise 0 radians points at +X instead of -Z like we want.
	cameraFront = glm::normalize(cameraDirection);

	updateCameraRotation(dx * mouseSensitivity, dy * mouseSensitivity);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

//--------------------------------------------------------------
float ofApp::randf(float start = 0.0, float end = 1.0)
{
	float r = ((float)rand()) / (float)RAND_MAX;
	r = r * (end - start) + start;
	return r;
}