#include "city.h"

city::city()
{
}

void city::newCity(int _x, int _y, int _id, string _name, vector<int> _connectedTo) {
	x = _x; 
	y = _y;
	id = _id; 
	name = _name; 
	for (int i = 0; i < _connectedTo.size() ; i++) {
		connectedTo[i] = _connectedTo[i]; 
	}
}

void city::draw() {
	ofSetColor(255);
	ofDrawCircle(x, y, 10);
	ofSetColor(0);
	ofDrawCircle(x, y, 8);
	ofDrawBitmapString(name, x - 25, y - 12);
}

