#include "ofApp.h"

/*
=================

Note vooraf; De stringWidth functie geeft een groter getal terug dan dat de string daadwerkelijk is.
Dus ik heb wat creatiefs moeten doen om het voor het oog kloppent te maken.

Ook werkt de ofLerp niet op hhSingle en hhMultiple. Heb nog niet ondekt waarom niet. 

=================
*/


void ofApp::setup() {
	string databasePath = ofToDataPath("huishoudens.db", true);
	ofLog() << databasePath << endl;
	db = new SQLite::Database(databasePath);

	font.load("montserrat.otf", ofGetWidth() / 30);
	fontLarge.load("montserrat.otf", ofGetWidth() / 20);



}

void ofApp::update() {
}

void ofApp::draw() {

	ofSetBackgroundColor(ofColor::black);

	SQLite::Statement query(*db, "SELECT * FROM huishoudens WHERE jaar=?");
	query.bind(1, ofToString(years[currentYear]));


	while (query.executeStep()) {
		hhTotal = query.getColumn("huishoudens_totaal").getInt()*1.0;
		
		/*
		===POGING#1===
		hhSingle = ofLerp(hhSingle, ((query.getColumn("hh_single").getInt()*1.0) / hhTotal) * 100, 0.01);
		hhMultiple = ofLerp(hhMultiple, ((query.getColumn("hh_multiple").getInt()*1.0) / hhTotal) * 100, 0.01);
				
		===POGING#2===
		hhSingle = ofLerp(hhSingle,(query.getColumn("hh_single").getInt()*1.0), 0.01);
		hhMultiple = ofLerp(hhSingle,(query.getColumn("hh_multiple").getInt()*1.0), 0.01);
		hhSingle = (hhSingle / hhTotal);
		hhMultiple = (hhMultiple / hhTotal);
		*/


		hhSingle = ((query.getColumn("hh_single").getInt()*1.0) / hhTotal) * 100;
		hhMultiple = ((query.getColumn("hh_multiple").getInt()*1.0) / hhTotal) * 100;
		hhMultipleNoKids = ofLerp(hhMultipleNoKids, ((query.getColumn("hh_multiple_nokids").getInt()*1.0) / hhTotal) * 100, 0.01);
		hhMultipleKids = ofLerp(hhMultipleKids, ((query.getColumn("hh_multiple_kids").getInt()*1.0) / hhTotal) * 100, 0.01);
		hhMultipleNotMarried = ofLerp(hhMultipleNotMarried, ((query.getColumn("hh_multiple_notmarried").getInt()*1.0) / hhTotal) * 100, 0.01);
		hhMultipleMarried = ofLerp(hhMultipleMarried, ((query.getColumn("hh_multiple_married").getInt()*1.0) / hhTotal) * 100, 0.01);
		hhMultipleSingleParent = ofLerp(hhMultipleSingleParent, ((query.getColumn("hh_multiple_singleparent").getInt()*1.0) / hhTotal) * 100, 0.01);


		if (ShowNumbers) {
			ofDrawBitmapString(hhTotal, ofGetWidth() - 200, ofGetHeight() - 150);
			ofDrawBitmapString(hhSingle, ofGetWidth() - 200, ofGetHeight() - 130);
			ofDrawBitmapString(hhMultiple, ofGetWidth() - 200, ofGetHeight() - 120);
			ofDrawBitmapString(hhMultipleNoKids, ofGetWidth() - 200, ofGetHeight() - 100);
			ofDrawBitmapString(hhMultipleKids, ofGetWidth() - 200, ofGetHeight() - 90);
			ofDrawBitmapString(hhMultipleNotMarried, ofGetWidth() - 200, ofGetHeight() - 80);
			ofDrawBitmapString(hhMultipleMarried, ofGetWidth() - 200, ofGetHeight() - 70);
			ofDrawBitmapString(hhMultipleSingleParent, ofGetWidth() - 200, ofGetHeight() - 60);
		}

		//Single of Multiple

		hhSingle = ofMap(hhSingle, 0, 100, 0, ofGetWidth() - 100);
		hhMultiple = ofMap(hhMultiple, 0, 100, 0, ofGetWidth() - 100);

		ofSetColor(200, 0, 0);
		ofDrawRectangle(50, (ofGetHeight() / 10), hhSingle, ofGetHeight() / 10);
		ofSetColor(200, 0, 0, 125);
		ofDrawRectangle(50 + hhSingle, (ofGetHeight() / 10), hhMultiple, ofGetHeight() / 10);
		ofSetColor(ofColor::white);
		font.drawString("Single Huishoudens", 50, (ofGetHeight() / 10));
		font.drawString("Meerdere Mensen", ofGetWidth() - 100 - (font.stringWidth("MeerdereMensen")), (ofGetHeight() / 10));

		//Kids or No Kids

		hhKids = hhMultipleKids + hhMultipleSingleParent;
		hhNoKids = 100 - hhKids;
		hhKids = ofMap(hhKids, 0, 100, 0, ofGetWidth() - 100);
		hhNoKids = ofMap(hhNoKids, 0, 100, 0, ofGetWidth() - 100);

		ofSetColor(0, 200, 0);
		ofDrawRectangle(50, (ofGetHeight() / 10) * 3, hhNoKids, ofGetHeight() / 10);
		ofSetColor(0, 200, 0, 125);
		ofDrawRectangle(50 + hhNoKids, (ofGetHeight() / 10) * 3, hhKids, ofGetHeight() / 10);
		ofSetColor(ofColor::white);
		font.drawString("Zonder Kinderen", 50, (ofGetHeight() / 10) * 3);
		font.drawString("Met Kinderen", ofGetWidth() - 100 - (font.stringWidth("MetKinderen")), (ofGetHeight() / 10) * 3);


		//Married or not Married

		hhMarried = hhMultipleMarried;
		hhNotMarried = hhMultiple - hhMultipleMarried;
		hhMarried = ofMap(hhMarried, 0, hhMultiple, 0, ofGetWidth() - 100);
		hhNotMarried = ofMap(hhNotMarried, 0, hhMultiple, 0, ofGetWidth() - 100);

		ofSetColor(0, 0, 200);
		ofDrawRectangle(50, (ofGetHeight() / 10) * 5, hhNotMarried, ofGetHeight() / 10);
		ofSetColor(0, 0, 200, 125);
		ofDrawRectangle(50 + hhNotMarried, (ofGetHeight() / 10) * 5, hhMarried, ofGetHeight() / 10);

		ofSetColor(ofColor::white);
		font.drawString("Ongehuwd", 50, (ofGetHeight() / 10) * 5);
		font.drawString("Getrouwd", ofGetWidth() - 75 - (font.stringWidth("Getrouwd")), (ofGetHeight() / 10) * 5);


		//Year

		fontLarge.drawString(ofToString(years[currentYear]), 50, (ofGetHeight() / 10) * 9);


	}

}

void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 20, ofGetWidth() - 20, 0, 8);

	year = ofToString(roundf(ofMap(x, 0, ofGetWidth(), years[0], years[8])));
}

void ofApp::keyPressed(int key) {
	if (key == 'n' || key == 'N') {
		ShowNumbers = !ShowNumbers;
	}

}
