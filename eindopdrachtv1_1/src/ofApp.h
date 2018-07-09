#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"
#include "city.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void mouseMoved(int x, int y);
	void keyPressed(int key);
	int getX(int value);
	int getY(int value);
	int adjustLocation(int value, int oldValue);

	float selector; 
	vector<city> cityList;
	city city;

	//To do: alle losse variable voor X en Y vervangen met een double of een ofVec2f. Zoek later wel uit hoe dat ook alweer werkte. 
	int x;
	int y;
	int carX;
	int carY;
	int trainX;
	int trainY;
	int cityX1;
	int cityY1;
	int cityX2;
	int cityY2; 

	int id;
	string name;
	string routeSelector; 

	int map = 1;

	ofTrueTypeFont font;

	int pinButtonNormal;
	int pinButtonCar;
	int pinButtonTrain;
	int pinButtonPod;
	int pinLerpPod;

	ofArduino arduino;
	void setupArduino(const int& version);
	void analogPinChanged(const int& pin);
	void digitalPinChanged(const int& pin);

private:

	SQLite::Database* db;
	SQLite::Statement* routeQuery;
	SQLite::Statement* cityQuery;

	int middleX;
	int middleY;
	int minX;
	int maxX;
	int minY;
	int maxY;
	float avgKm;
	float modCar;
	float modTrain;
	
	int oldCityId;
	int newCityId;

	int city1;
	int city2;
	int car; 
	int train; 

};