#pragma once

#include "ofMain.h"
#define STARTY 300

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		int alkmaarTijd = 195; 
		int alkmaarKM = 252; 
		int alkmaarKMU = 77;

		int meppelTijd = 240; 
		int meppelKM = 255; 
		int meppelKMU = 63; 

		int rotterdamTijd = 136; 
		int rotterdamKM = 200; 
		int rotterdamKMU = 88; 

		int munsterTijd = 267; 
		int munsterKM = 223; 
		int munsterKMU = 50; 
		
};
