#include "city.h"

city::city()
{
}

void city::newCity(int _id, int _x, int _y, int _carX, int _carY, int _trainX, int _trainY, string _name) {
	x = _x;
	y = _y;
	carX = _carX;
	carY = _carY;
	trainX = _trainX;
	trainY = _trainY; 
	id = _id;
	name = _name;
}

void city::draw() {
	ofSetColor(255);
	ofDrawCircle(x, y, 10);
	ofSetColor(0);
	ofDrawCircle(x, y, 8);
	ofDrawBitmapString(name, x - 25, y - 12);
}

