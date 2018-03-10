#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"
//of #include "SQLiteCpp.h" !

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mouseMoved(int x, int y);

private:
	ofTrueTypeFont font;

	int selectedYear;
	int currentYear;

	int minYear;
	int maxYear;

	map<string, double> populationByCountry;
	map<string, double> healthByCountry;
	map<string, double> incomeByCountry;
	vector<string> countryList; 

	SQLite::Database* db;
	SQLite::Statement* regionQuery;
	SQLite::Statement* populationQuery;
	SQLite::Statement* healthQuery;
	SQLite::Statement* incomeQuery;

	double maxHealth;
	double maxIncome;
	int maxPopulation;
};