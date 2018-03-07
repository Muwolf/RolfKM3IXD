#include "ofApp.h"

void ofApp::setup() {
	string databasePath = ofToDataPath("huishoudens.sqlite", true);
	ofLog() << databasePath << endl;
	db = new SQLite::Database(databasePath);
	
}

void ofApp::update() {
}

void ofApp::draw() {
	SQLite::Statement query(*db, "SELECT * FROM population WHERE jaar=?");
	query.bind(1, years[currentYear]);

	while (query.executeStep()) {
		hhTotaal = ofLerp(hhTotaal, query.getColumn("huishoudens_totaal").getInt(), 0.01);
		hhSingle = ofLerp(hhSingle, query.getColumn("hh_single").getInt(), 0.01);
		hhMultiple = ofLerp(hhMultiple, query.getColumn("hh_Multiple").getInt(), 0.01); 

		hhSingle = ofMap(hhSingle, 0, hhTotaal, 0, MAXCIRCLERADIUS, false); 
		hhMultiple = ofMap(hhMultiple, 0, hhTotaal, 0, MAXCIRCLERADIUS, false);


		ofDrawCircle(ofGetWidth()*0.33, MAXCIRCLERADIUS, hhSingle);
		ofDrawCircle(ofGetWidth()*0.66, MAXCIRCLERADIUS, hhMultiple);
	}

}

void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 5);

	year = ofToString(roundf(ofMap(x, 0, ofGetWidth(), years[0], years[4])));
}
