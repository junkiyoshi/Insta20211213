#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int base_y = -200; base_y <= 200; base_y += 200) {

		auto noise_seed = ofRandom(1000);
		for (int x = -300; x <= 300; x += 20) {

			auto y = ofMap(ofNoise(noise_seed, x * 0.005 + ofGetFrameNum() * 0.025), 0, 1, -100, 100);
			this->draw_arrow(glm::vec2(x, base_y), glm::vec2(x, base_y + y), 18, ofColor(39));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	if (glm::length(distance) > size * 0.1) {

		ofPushMatrix();
		ofTranslate(target);

		ofSetColor(color);
		ofFill();
		ofBeginShape();
		ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)));
		ofEndShape();

		ofBeginShape();
		ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25);
		ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25);
		ofEndShape();

		ofPopMatrix();
	}

	ofDrawCircle(location, 5);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}