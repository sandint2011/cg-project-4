#include "ofApp.h"
#include <vector>
#include <random>

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();

	ofEnableDepthTest();
	glEnable(GL_CULL_FACE);

	ofSetBackgroundColor(135, 205, 235, 255);

	// Mesh and VBO setup...

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
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Camera settings.
	const float nearClip = 15;
	const float farClip = 200;

	const float startFade = farClip * 0.7;
	const float endFade = farClip * 0.9;

	float aspectRatio = static_cast<float>(ofGetViewportWidth()) / static_cast<float>(ofGetViewportHeight());

	// Movel-view-projection.
	glm::mat4 model = (
		glm::scale(glm::vec3(1, 1, 1))
		);

	glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, nearClip, farClip);

	// Shader drawing.
	shader.begin();

	// Setup lighting parameters.
	shader.setUniform3f("lightDirection", normalize(glm::vec3(-1, 1, 1)));
	shader.setUniform3f("lightColor", glm::vec3(1, 1, 0.9));
	shader.setUniform3f("ambientColor", glm::vec3(0.1));

	// Pass camera info to shader.
	shader.setUniform3f("cameraPosition", cameraPosition);
	shader.setUniform1f("startFade", startFade);
	shader.setUniform1f("endFade", endFade);

	// Draw stuff...

	shader.end();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '`')
	{
		needsShaderReload = true;
	}

	const float cameraSpeed = 20 * 32;
	const float sprint = 5;
	const float dt = ofGetLastFrameTime();

	// Forward / backward.
	if (key == 'w')
		cameraPosition += cameraFront * cameraSpeed * dt;
	else if (key == 'W')
		cameraPosition += cameraFront * cameraSpeed * sprint * dt;
	if (key == 's')
		cameraPosition -= cameraFront * cameraSpeed * dt;
	else if (key == 'S')
		cameraPosition -= cameraFront * cameraSpeed * sprint * dt;

	// Left / right.
	if (key == 'a')
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
	else if (key == 'A')
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * sprint * dt;
	if (key == 'd')
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
	else if (key == 'D')
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * sprint * dt;

	// Up / down.
	if (key == 'q')
		cameraPosition += cameraUp * cameraSpeed * dt;
	else if (key == 'Q')
		cameraPosition += cameraUp * cameraSpeed * sprint * dt;
	if (key == 'e')
		cameraPosition -= cameraUp * cameraSpeed * dt;
	else if (key == 'E')
		cameraPosition -= cameraUp * cameraSpeed * sprint * dt;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	// Get the mouse's change ins position since last frame.
	float dx = x - lastMouseX;
	float dy = y - lastMouseY;
	lastMouseX = x;
	lastMouseY = y;

	// Apply sensitivity to mouse movement.
	const float sensitivity = 0.5f;
	dx *= sensitivity;
	dy *= sensitivity;

	// Store camera rotation in radians.
	cameraHead += glm::radians(dx);
	cameraPitch += glm::radians(dy);

	// Clamp the pitch.
	cameraPitch = CLAMP(cameraPitch, glm::radians(-89.0f), glm::radians(89.0f));

	// Calculate camera direction.
	cameraDirection.x = cos(cameraHead - glm::radians(90.0f)) * cos(cameraPitch); // Sutract 90 degrees from head because otherwise 0 radians points at +X instead of -Z like we want.
	cameraDirection.y = -sin(cameraPitch); // Negative because otherwise we're doing inverted Y and that's gross.
	cameraDirection.z = sin(cameraHead - glm::radians(90.0f)) * cos(cameraPitch); // Sutract 90 degrees from head because otherwise 0 radians points at +X instead of -Z like we want.
	cameraFront = glm::normalize(cameraDirection);
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