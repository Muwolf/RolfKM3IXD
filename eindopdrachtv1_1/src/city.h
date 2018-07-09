#pragma once

#define _CITY
#include "ofMain.h"

class city
{
public:

	void newCity(int _id, int _x, int _y, ofTrueTypeFont _font, string _name);
	void draw(); 

	int id;
	int x;
	int y;	
	string name;
	ofTrueTypeFont font;
	int stringWidth;
	int stringHeight;

	ofColor backgroundNameColor = 0x092869;

	city();
};

