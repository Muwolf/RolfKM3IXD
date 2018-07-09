#include "ofApp.h"

void ofApp::setup() {

	string databasePath = ofToDataPath("cities.db", true);
	db = new SQLite::Database(databasePath);

	middleX = db->execAndGet("SELECT AVG(longitude) FROM city").getInt();
	middleY = db->execAndGet("SELECT AVG(latitude) FROM city").getInt();
	minX = (db->execAndGet("SELECT MIN(longitude) FROM city").getInt()) - middleX;
	maxX = (db->execAndGet("SELECT MAX(longitude) FROM city").getInt()) - middleX;
	minY = (db->execAndGet("SELECT MIN(latitude) FROM city").getInt()) - middleY;
	maxY = (db->execAndGet("SELECT MAX(latitude) FROM city").getInt()) - middleY;
	avgKm = ofToFloat(db->execAndGet("SELECT AVG(distance_km) FROM connection"));
	modCar = (db->execAndGet("SELECT AVG(car_min) FROM connection").getInt()) / avgKm;
	modTrain = (db->execAndGet("SELECT AVG(train_min) FROM connection").getInt()) / avgKm;


}

void ofApp::update() {

	cityQuery = new SQLite::Statement(*db, "SELECT o.id as id, o.city_id1 as id1, o.city_id2 as id2, c.id as city_id, c.name as name, longitude as x, latitude as y FROM connection o LEFT JOIN city c ON o.city_id1 = c.id OR o.city_id2 = c.id ORDER BY c.id");
	while (cityQuery->executeStep()) {

		newCityId = cityQuery->getColumn("city_id").getInt();

		if (newCityId != oldCityId) {
			x = getX((cityQuery->getColumn("x")).getInt());
			y = getY((cityQuery->getColumn("y")).getInt());
			id = newCityId;
			carX = 0;
			carY = 0;
			trainX = 0;
			trainY = 0;
			string name = (cityQuery->getColumn("name"));
			city.newCity(id, x, y, carX, carY, trainX, trainY, name);
			cityList.push_back(city);
		}
		oldCityId = newCityId;
	}
	cityQuery->reset();

	routeQuery = new SQLite::Statement(*db, "SELECT city_id1, city_id2, car_min, train_min FROM connection");
	while (cityQuery->executeStep()) {
		city1 = cityQuery->getColumn("city_id1").getInt();
		city2 = cityQuery->getColumn("city_id2").getInt();
		car = cityQuery->getColumn("car_min").getInt();
		train = cityQuery->getColumn("train_min").getInt();
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i].id == city1 || cityList[i].id == city2) {
				cityList[i].carX = adjustLocation(car, cityList[i].carX);
				cityList[i].carY = adjustLocation(car, cityList[i].carY);
				cityList[i].trainX = adjustLocation(train, cityList[i].trainX);
				cityList[i].trainY = adjustLocation(train, cityList[i].trainY);
				ofLog() << cityList[i].name << ": CarX: " << cityList[i].carX << " CarY: " << cityList[i].carY;
			}
		}
	
	}
}



void ofApp::draw() {
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetBackgroundColor(250, 242, 229);

	while (cityQuery->executeStep()) {
		city1 = cityQuery->getColumn("id1").getInt();
		city2 = cityQuery->getColumn("id2").getInt();
		cityX1 = 0;
		cityY1 = 0;
		cityX2 = 0;
		cityY2 = 0;

		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i].id == city1) {
				cityX1 = cityList[i].x;
				cityY1 = cityList[i].y;
			}
			if (cityList[i].id == city2) {
				cityX2 = cityList[i].x;
				cityY2 = cityList[i].y;
			}
			if (cityX1 != 0 && cityY1 != 0 && cityX2 != 0 && cityY2 != 0) {
				ofSetColor(200, 0, 0);
				ofDrawLine(cityX1, cityY1, cityX2, cityY2);
			}
		}
	}
	cityQuery->reset();

	for (int i = 0; i < cityList.size(); i++) {
		cityList[i].draw();
	}

	while (!cityList.empty()) {
		cityList.pop_back();
	}
}

void ofApp::mouseMoved(int x, int y) {

	selector = ofMap(x, 20, ofGetWidth() - 20, 0, 1023);

}


int ofApp::getX(int value) {
	int valueX;
	valueX = ofMap((value - middleX), minX, maxX, ofGetWidth() / -2.5, ofGetWidth() / 2.5);
	return valueX;

}

int ofApp::getY(int value) {
	int valueY;
	valueY = ofMap((value - middleY), minY, maxY, ofGetHeight() / 2.5, ofGetHeight() / -2.5);
	return valueY;
}

int ofApp::adjustLocation(int value, int oldValue) {
	if (oldValue > 0) {
		return (oldValue + value);
	}
	else {
		return (oldValue - value);
	}
}