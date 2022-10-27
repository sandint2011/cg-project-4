#include "ofApp.h"
#include <vector>
#include <random>
#include "SimpleDrawNode.h"
#include "CameraMatrices.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();

	ofEnableDepthTest();
	glEnable(GL_CULL_FACE);

	//ofSetBackgroundColor(135, 205, 235, 255);

	// Load mesh and invert its normals.
	vboMesh.load("torus.ply");
	vboMesh.flatNormals();
	for (int i = 0; i < vboMesh.getNumNormals(); i++)
	{
		vboMesh.setNormal(i, -vboMesh.getNormal(i));
	}

	// Add a red torus to the scene graph.
	root.childNodes.emplace_back(new SimpleDrawNode(vboMesh, shader, glm::vec3(1, 0.25, 0.25)));
	root.childNodes.back()->transform = glm::rotate(glm::radians(90.0f), glm::vec3(1, 1, 1));
	meshNode = root.childNodes.back();

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

	// DRAW A RED TORUS USING THE SCENE GRAPH (doesn't work).
	root.drawSceneGraph(cameraMatrices);

	// DRAW A BLUE TORUS MANUALLY (works fine).
	mat4 mvp = mat4(cameraMatrices.getProj() * cameraMatrices.getView() * mat4 {translate(vec3(1, 0, 0)) });
	shader.begin();
	// Setup lighting parameters.
	shader.setUniform3f("lightDirection", normalize(vec3(-1, 1, 1)));
	shader.setUniform3f("lightColor", vec3(1, 1, 0.9));
	shader.setUniform3f("ambientColor", vec3(0.1));
	// Set up transforms.
	shader.setUniformMatrix4f("mvp", mvp);
	shader.setUniformMatrix3f("normalMatrix", inverse(transpose(mat4{})));
	// Color and draw.
	shader.setUniform3f("meshColor", vec3(0.25, 0.25, 1));
	vboMesh.draw();
	shader.end();
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