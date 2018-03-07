#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(50);
	font.load("BAUHS93.ttf", 64);

	string databasePath = ofToDataPath("roslingdb.sqlite", true);
	db = new SQLite::Database(databasePath);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	SQLite::Statement query(*db, "SELECT * FROM population WHERE year=?");
	query.bind(1, years[currentYear]);

	while (query.executeStep()) {
		/*		ofLog() << query.getColumn("year") << " "
						<< query.getColumn("nl")
						<< endl;
		*/


		currentPopulation_NL = ofLerp(currentPopulation_NL, query.getColumn("nl").getInt(), 0.01);

		ofSetColor(ofColor::orange);
		ofDrawCircle((ofGetWidth() * 0.25), 350, currentPopulation_NL * 5);
		ofSetColor(ofColor::black);
		font.drawString("Nederland", (ofGetWidth() *0.25) - (font.stringWidth("Nederland") / 2), 800);

		currentPopulation_AU = ofLerp(currentPopulation_AU, query.getColumn("au").getInt(), 0.01);

		ofSetColor(ofColor::yellow);
		ofDrawCircle((ofGetWidth() * 0.5), 350, currentPopulation_AU * 5);
		ofSetColor(ofColor::black);
		font.drawString("Australie", (ofGetWidth() * 0.5) - (font.stringWidth("Australie") / 2), 800);

		currentPopulation_ZH = ofLerp(currentPopulation_ZH, query.getColumn("zh").getInt(), 0.01);

		ofSetColor(ofColor::red);
		ofDrawCircle((ofGetWidth() * 0.75), 350, currentPopulation_ZH * 5);
		ofSetColor(ofColor::black);
		font.drawString("China", (ofGetWidth() * 0.75) - (font.stringWidth("China") / 2), 800);

		

		font.drawString(year, (ofGetWidth() / 2) - (font.stringWidth(year) / 2), 950);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 5);

	year = ofToString(roundf(ofMap(x, 0, ofGetWidth(), years[0], years[4])));
}