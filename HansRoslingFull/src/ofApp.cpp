#include "ofApp.h"

void ofApp::setup() {
	ofSetCircleResolution(50);

	font.load("montserrat.otf", 64);

	string databasePath = ofToDataPath("roslingdb.sqlite", true);
	db = new SQLite::Database(databasePath);

	// de drie queries de we gaan gebruiken (en herbruiken)
	populationQuery = new SQLite::Statement(*db, "SELECT * FROM population WHERE year=?");
	healthQuery = new SQLite::Statement(*db, "SELECT * FROM lifeexp WHERE year=?");
	incomeQuery = new SQLite::Statement(*db, "SELECT * FROM income WHERE year=?");
	regionQuery = new SQLite::Statement(*db, "SELECT * FROM region WHERE country =?");

	// selecteer het min en max jaar uit de database
	// (hoeft niet via een SQLite::Statement, want levert maar 1 getal op)
	minYear = db->execAndGet("SELECT MIN(year) FROM population").getInt();
	ofLog() << "minYear=" << minYear << endl;

	maxYear = db->execAndGet("SELECT MAX(year) FROM population").getInt();
	ofLog() << "maxYear=" << maxYear << endl;

	// zelfde truc als voor min en max van jaar
	maxHealth = db->execAndGet("SELECT MAX(life_exp) FROM lifeexp").getDouble();
	maxIncome = db->execAndGet("SELECT MAX(income) FROM income").getDouble();
	maxPopulation = db->execAndGet("SELECT MAX(population) FROM population").getInt();

	selectedYear = minYear;
	currentYear = 0;

	/* SQLite::Statement query(*db, "SELECT * FROM region");
	while (query.executeStep()) {
		string country = query.getColumn("country").getText();
		string region = query.getColumn("region").getText();
		countryList.push_back(country);
		regionList.push_back(region);
	}

	for (int i = 0; i < countryList.size(); i++) {
		ofLog() << countryList[i] << " is part of " << regionList[i] << endl;
	}*/
}


void ofApp::update() {
	if (currentYear != selectedYear) { // alleen als er een nieuw jaar geselecteerd is alles ophalen
		currentYear = selectedYear;
		//ofLog() << "selectedYear = " << selectedYear << endl;

		populationQuery->bind(1, selectedYear); // vervang het 1e vraagteken door selectedYear
		while (populationQuery->executeStep()) {
			//ofLog() << "country=" << populationQuery->getColumn("country")
			//	<< " pop=" << populationQuery->getColumn("population");
			const string& country = populationQuery->getColumn("country");
			populationByCountry[country] = populationQuery->getColumn("population").getDouble();
		}
		populationQuery->reset(); // zet de query weer terug naar de beginstand (met ?)

		healthQuery->bind(1, selectedYear); // vervang het 1e vraagteken door selectedYear
		while (healthQuery->executeStep()) {
			//ofLog() << "country=" << healthQuery->getColumn("country")
			//	<< " life_exp=" << healthQuery->getColumn("life_exp");
			const string& country = healthQuery->getColumn("country");
			healthByCountry[country] = healthQuery->getColumn("life_exp").getDouble();
		}
		healthQuery->reset(); // zet de query weer terug naar de beginstand (met ?)

		incomeQuery->bind(1, selectedYear); // vervang het 1e vraagteken door selectedYear
		while (incomeQuery->executeStep()) {
			//ofLog() << "country=" << incomeQuery->getColumn("country")
			//	<< " income=" << incomeQuery->getColumn("income");
			const string& country = incomeQuery->getColumn("country");
			incomeByCountry[country] = incomeQuery->getColumn("income").getDouble();
		}
		incomeQuery->reset(); // zet de query weer terug naar de beginstand (met ?)

		regionQuery->bind(1, incomeByCountry);
	}

}

void ofApp::draw() {
	ofSetColor(ofColor::black);
	font.drawString(ofToString(currentYear), ofGetWidth() - 300, ofGetHeight() / 2);

	// loop per land door de lijst populationByCountry heen
	for (auto& countryAndPopulation : populationByCountry) {
		string country = countryAndPopulation.first;

		double population = populationByCountry[country];
		double health = healthByCountry[country];
		double income = incomeByCountry[country];



		/*
		ofLog() << "country=" << country
		<< " pop=" << population
		<< " health=" << health
		<< " income=" << income << endl;
		*/

		if (population > 0 && health > 0 && income > 0) { 



			
			/*
			if (region == "Sub-Saharan Africa") {
				ofSetHexColor(0x000000);
			}
			else if (region == "South Asia") {
				ofSetHexColor(0xF4C300);
			}
			else if (region == "Middle East & North Africa") {
				ofSetHexColor(0x401A4C);
			}
			else if (region == "America") {
				ofSetHexColor(0xDF0024);
			}
			else if (region == "Europe & Central Asia") {
				ofSetHexColor(0x0085C7);
			}
			else if (region == "East Asia & Pacific") {
				ofSetHexColor(0x009F3D);
			}*/
			ofNoFill();

			ofDrawCircle(ofMap(income, 0, maxIncome, 100, ofGetWidth() - 100),
				ofMap(health, 0, maxHealth, ofGetHeight() - 100, 100),
				ofMap(population, 0, maxPopulation, 1, 200));


		}
		else {
			/*
			ofLog() << "incomplete data for country=" << country
			<< " pop=" << population
			<< " health=" << health
			<< " income=" << income << endl;
			*/
		}
	}
}

void ofApp::keyPressed(int key) {

}

void ofApp::mouseMoved(int x, int y) {
	selectedYear = ofMap(x, 20, ofGetWidth() - 20, minYear, maxYear, true);
}