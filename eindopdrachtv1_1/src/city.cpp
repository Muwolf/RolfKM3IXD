#include "city.h"

city::city()
{
}

void city::newCity(int _id, int _x, int _y, ofTrueTypeFont _font, string _name) {
	id = _id;
	x = _x;
	y = _y;
	name = _name;
	font = _font;
	stringWidth = font.stringWidth(name);
	stringHeight = font.stringHeight("Standaart hoogte");

}

void city::draw() {
	ofSetColor(0);
	ofDrawCircle(x, y, 10);
	ofSetColor(255);
	ofDrawCircle(x, y, 8);
	ofSetColor(9, 40, 150);
	ofDrawRectRounded((x - (stringWidth/2)), y - (stringHeight*2), stringWidth*1.2, stringHeight*1.4, stringHeight/4) ;
	ofSetColor(255);
	font.drawString(name, (x - (stringWidth / 2.45)), y - (stringHeight*1));
}

