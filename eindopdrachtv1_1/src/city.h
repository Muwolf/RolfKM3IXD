#pragma once

#define _CITY
#include "ofMain.h"

class city
{
public:

	void newCity(int _x, int _y, int _id, string _name, vector<int> _connectedTo);
	void draw(); 

	int x = 0; 
	int y = 0; 
	int id = 0; 
	string name = ""; 
	vector<int> connectedTo;


	city();
};

