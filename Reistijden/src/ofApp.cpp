#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(52);

	ofSetColor(255);
	ofDrawBitmapString("Reistijd in minuten", 50, STARTY + 15);
	ofSetColor(255, 10, 10);
	ofRect(50, STARTY - alkmaarTijd, 30, alkmaarTijd);
	ofSetColor(10, 255, 10);
	ofRect(100, STARTY - meppelTijd, 30, meppelTijd);
	ofSetColor(10, 10, 255);
	ofRect(150, STARTY - rotterdamTijd, 30, rotterdamTijd);
	ofSetColor(255, 255, 10);
	ofRect(200, STARTY - munsterTijd, 30, munsterTijd);

	ofSetColor(255);
	ofDrawBitmapString("Afstand in Kilometers", 300, STARTY + 15);
	ofSetColor(255, 10, 10);
	ofRect(300, STARTY - alkmaarKM, 30, alkmaarKM);
	ofSetColor(10, 255, 10);
	ofRect(350, STARTY - meppelKM, 30, meppelKM);
	ofSetColor(10, 10, 255);
	ofRect(400, STARTY - rotterdamKM, 30, rotterdamKM);
	ofSetColor(255, 255, 10);
	ofRect(450, STARTY - munsterKM, 30, munsterKM);

	ofSetColor(255);
	ofDrawBitmapString("Kilometers per uur", 550, STARTY + 15);
	ofSetColor(255, 10, 10);
	ofRect(550, STARTY - alkmaarKMU, 30, alkmaarKMU);
	ofSetColor(10, 255, 10);
	ofRect(600, STARTY - meppelKMU, 30, meppelKMU);
	ofSetColor(10, 10, 255);
	ofRect(650, STARTY - rotterdamKMU, 30, rotterdamKMU);
	ofSetColor(255, 255, 10);
	ofRect(700, STARTY - munsterKMU, 30, munsterKMU);

	
	for (int i = 0; i < 15; i++) {
		ofSetColor(0);
		ofDrawRectangle(50, 300 - (i * 20), 700, 1);
		ofSetColor(255);
		ofDrawBitmapString(ofToString(i * 20), 20, 305 - (i * 20));
	}

	ofSetColor(255);
	ofDrawBitmapString("Van Maastricht naar:", 50, 340);

	ofSetColor(255, 10, 10);
	ofRect(50, 350, 10, 10);
	ofSetColor(255); 
	ofDrawBitmapString("Alkmaar", 65, 360); 


	ofSetColor(10, 255, 10);
	ofRect(50, 365, 10, 10);
	ofSetColor(255); 
	ofDrawBitmapString("Meppel", 65, 375);

	ofSetColor(10, 10, 255);
	ofRect(50, 380, 10, 10);
	ofSetColor(255);
	ofDrawBitmapString("Alkmaar", 65, 390);

	ofSetColor(255, 255, 10);
	ofRect(50, 395, 10, 10);
	ofSetColor(255);
	ofDrawBitmapString("Munster", 65, 405);

}
