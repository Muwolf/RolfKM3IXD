#pragma once

#define _CITY
#include "ofMain.h"

class city
{
public:

	void newCity(int _id, int _x, int _y, int _carX, int _carY, int _trainX,  int _trainY, string _name);
	void draw(); 

	int x;
	int y;
	int carX;
	int carY;
	int trainX;
	int trainY; 
	int id;
	string name;

	city();
};

