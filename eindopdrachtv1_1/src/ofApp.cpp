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

}

void ofApp::update() {

	routeQuery = new SQLite::Statement(*db, "SELECT o.id as id, o.city_id1 as id1, o.city_id2 as id2, distance_km as km, car_min as car, train_min as train, c.id as city_id, c.name as name, longitude as x, latitude as y FROM connection o LEFT JOIN city c ON o.city_id1 = c.id OR o.city_id2 = c.id ORDER BY c.id");
	while (routeQuery->executeStep()) {

		newCityId = routeQuery->getColumn("city_id").getInt();

		if (newCityId != oldCityId) {
			x = getX((routeQuery->getColumn("x")).getInt());
			y = getY((routeQuery->getColumn("y")).getInt());
			id = newCityId;
			string name = (routeQuery->getColumn("name"));
			city.newCity(x, y, id, name, connectedTo);
			cityList.push_back(city);
		}
		oldCityId = newCityId;
	}
	routeQuery->reset();

	while (routeQuery->executeStep()) {
		city1 = routeQuery->getColumn("id1").getInt();
		city2 = routeQuery->getColumn("id2").getInt();
		for (int i = 0; i < cityList.size(); i++) {
			if (city1 == cityList[i].id) {
				cityList[i].connectedTo.push_back(city2);
				
			}
			if (city2 == cityList[i].id) {
				cityList[i].connectedTo.push_back(city1);
			}
		}

	}
	routeQuery->reset();
}



void ofApp::draw() {
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetBackgroundColor(250, 242, 229);

	for (int i = 0; i < cityList.size(); i++) {
		cityList[i].draw();
	}

	while (!cityList.empty()) {
		cityList.pop_back();
	}
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