#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	int radius_span = 1;
	int deg_span = 1;
	float noise_value;
	ofColor color;

	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int radius = 0; radius < 700; radius += radius_span) {
		for (int deg = 0; deg < 360; deg += deg_span) {

			noise_value = ofNoise(ofGetFrameNum() * 0.008 - radius * 0.005, 100 * cos(deg * DEG_TO_RAD) * 0.0025, 100 * sin(deg * DEG_TO_RAD) * 0.0025);
			//color.setHsb( 255 * noise_value, 255, 255);
			color = ofColor(255 * noise_value);
			ofSetColor(color);

			ofBeginShape();

			ofVertex(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			ofVertex((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD));
			ofVertex((radius + radius_span) * cos((deg + deg_span) * DEG_TO_RAD), (radius + radius_span) * sin((deg + deg_span) * DEG_TO_RAD));
			ofVertex(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD));

			ofEndShape(true);
		}
	}

	this->fbo.end();

	//if (ofGetFrameNum() < 1800) {
	//	this->fbo.readToPixels(this->pixels);
	//	this->image.setFromPixels(this->pixels);
	//	this->image.saveImage("save_image/" + std::to_string(ofGetFrameNum()) + ".png");
	//}

}

//--------------------------------------------------------------
void ofApp::draw() {
	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
