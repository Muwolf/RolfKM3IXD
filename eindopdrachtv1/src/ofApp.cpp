#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	string databasePath = ofToDataPath("cities.db.sql", true);
	db = new SQLite::Database(databasePath);
	ofLog() << db << endl; 


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}