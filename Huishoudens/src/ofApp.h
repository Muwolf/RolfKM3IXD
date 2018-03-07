#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

#define MAXCIRCLERADIUS 400

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void mouseMoved(int x, int y);

	string year;
	int currentYear = 0;

	int hhTotaal = 0; 
	int hhSingle = 0; 
	int hhMultiple = 0; 


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
