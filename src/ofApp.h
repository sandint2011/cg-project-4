#pragma once

#include <vector>
#include "ofMain.h"
#include "SceneGraphNode.h"
#include "Camera.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	SceneGraphNode root;
	std::shared_ptr<SceneGraphNode> meshNode;

	ofVboMesh vboMesh;
	ofShader shader;

	// Helper functions.
	float randf(float start, float end);

	// Professor's camera.
	Camera camera{ glm::vec3(0, 0, 2) };
	glm::vec3 velocity;
	int prevMouseX = ofGetViewportWidth() / 2;
	int prevMouseY = ofGetViewportHeight() / 2;
	float mouseSensitivity = 0.02f;
	float cameraHead = 0;
	float cameraPitch = 0;
	glm::vec3 cameraDirection = glm::vec3(0, 0, 0);
	glm::vec3 cameraFront = glm::vec3(0, 0, -1);
	glm::vec3 cameraUp = glm::vec3(0, 1, 0);
	void updateCameraRotation(float dx, float dy);

	// Shader reloading.
	bool needsShaderReload = true;
	void reloadShaders();
};
