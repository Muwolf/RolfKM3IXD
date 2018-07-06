#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();



		SQLite::Database* db;
		SQLite::Statement* Query; 
};
