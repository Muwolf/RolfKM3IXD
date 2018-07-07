#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"
#include "city.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	int getX(int value); 
	int getY(int value);

	vector<city> cityList;
	vector<int> connectedTo;
	city city;  

	int x = 0;
	int y = 0;
	int x2 = 0; 
	int y2 = 0;
	int id = 0; 
	string name = ""; 


private:

	SQLite::Database* db;
	SQLite::Statement* routeQuery;

	int middleX = 0;
	int middleY = 0;

	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;

	int oldId = 0; 
	int newId = 0; 

	int oldCityId = 0; 
	int newCityId = 0; 

	int city1 = 0; 
	int city2 = 0; 

	int i; 
	int j; 

};