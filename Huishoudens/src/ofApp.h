#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

#define MAXSIZE 500

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void mouseMoved(int x, int y);
	void keyPressed(int key);

	string year;
	int currentYear = 0;

	float hhTotal = 0; 
	float hhSingle = 0; 
	float hhMultiple = 0; 
	float hhMultipleNoKids = 0; 
	float hhMultipleKids = 0; 
	float hhMultipleNotMarried = 0; 
	float hhMultipleMarried = 0; 
	float hhMultipleSingleParent = 0; 

	float hhKids;
	float hhNoKids; 
	float hhMarried; 
	float hhNotMarried; 

	bool ShowNumbers = true; 

	ofTrueTypeFont font;
	ofTrueTypeFont fontLarge;


	int years[9] = { 1995,
					 2000,
					 2005,
					 2010,
					 2012,
					 2013,
					 2014,
					 2015,
					 2016 };

	SQLite::Database* db;
};
