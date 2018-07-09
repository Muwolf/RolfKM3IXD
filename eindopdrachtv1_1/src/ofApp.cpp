#include "ofApp.h"

void ofApp::setup() {
	
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	arduino.connect("COM3");
	arduino.sendFirmwareVersionRequest();


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

	font.load("Frutiger.otf", 15);

	pinButtonNormal = 5; 
	pinButtonCar = 6; 
	pinButtonTrain = 7;
	pinButtonPod = 4; 
	pinLerpPod = 0; 
}

void ofApp::update() {

	cityQuery = new SQLite::Statement(*db, "SELECT o.city_id1 as id1, o.city_id2 as id2, c.id as city_id, c.name as name, longitude as x, latitude as y FROM connection o LEFT JOIN city c ON o.city_id1 = c.id OR o.city_id2 = c.id ORDER BY c.id");
	while (cityQuery->executeStep()) {

		newCityId = cityQuery->getColumn("city_id").getInt();

		if (newCityId != oldCityId) {
			id = newCityId;
			x = getX((cityQuery->getColumn("x")).getInt());
			y = getY((cityQuery->getColumn("y")).getInt());
			string name = (cityQuery->getColumn("name"));
			city.newCity(id, x, y, font, name);
			cityList.push_back(city);
		}
		oldCityId = newCityId;
	}
	cityQuery->reset();

	routeQuery = new SQLite::Statement(*db, "SELECT city_id1, city_id2, (car_min/? - distance_km)/2  as car, (train_min/? - distance_km)/2 as train FROM connection");
	routeQuery->bind(1, modCar);
	routeQuery->bind(2, modTrain);

	while (routeQuery->executeStep()) {
		city1 = routeQuery->getColumn("city_id1").getInt();
		city2 = routeQuery->getColumn("city_id2").getInt();
		car = routeQuery->getColumn("car").getInt();
		train = routeQuery->getColumn("train").getInt();
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i].id == city1 || cityList[i].id == city2) {
				if (map == 2) {
					cityList[i].x = adjustLocation(car, cityList[i].x);
					cityList[i].y = adjustLocation(car, cityList[i].y);
				}
				else if (map == 3) {
					cityList[i].x = adjustLocation(train, cityList[i].x);
					cityList[i].y = adjustLocation(train, cityList[i].y);
				}
				else if (map == 4) {
					if (cityList[i].name != "Utrecht") {
						if (selector < 1) {
							cityList[i].x = ofLerp(adjustLocation(car, cityList[i].x), cityList[i].x, selector);
							cityList[i].y = ofLerp(adjustLocation(car, cityList[i].y), cityList[i].y, selector);
						}
						else {
							cityList[i].x = ofLerp(cityList[i].x, adjustLocation(train, cityList[i].x), selector - 1);
							cityList[i].y = ofLerp(cityList[i].y, adjustLocation(train, cityList[i].y), selector - 1);
						}
					}
				}
			}
		}
	}
	routeQuery->reset();
}



void ofApp::draw() {
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetBackgroundColor(255);

	while (cityQuery->executeStep()) {
		city1 = cityQuery->getColumn("id1").getInt();
		city2 = cityQuery->getColumn("id2").getInt();
		cityX1 = ofGetWidth();
		cityY1 = ofGetHeight();
		cityX2 = ofGetWidth();
		cityY2 = ofGetHeight();

		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i].id == city1) {
				cityX1 = cityList[i].x;
				cityY1 = cityList[i].y;
			}

			if (cityList[i].id == city2) {
				cityX2 = cityList[i].x;
				cityY2 = cityList[i].y;
			}

			if (cityX1 != ofGetWidth() && cityY1 != ofGetHeight() && cityX2 != ofGetWidth() && cityY2 != ofGetHeight()) {
				ofSetColor(255, 179, 16);
				ofSetLineWidth(5);
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

void ofApp::setupArduino(const int& version) {

	//Look for arduino, and show firmware
	ofLog() << "Arduino firmware found " << arduino.getFirmwareName()
		<< arduino.getMajorFirmwareVersion()
		<< arduino.getMinorFirmwareVersion() << endl;

	//Setup pins
	arduino.sendDigitalPinMode(pinButtonNormal, ARD_INPUT);
	arduino.sendDigitalPinMode(pinButtonCar, ARD_INPUT);
	arduino.sendDigitalPinMode(pinButtonTrain, ARD_INPUT);
	arduino.sendDigitalPinMode(pinButtonPod, ARD_INPUT);
	arduino.sendAnalogPinReporting(pinLerpPod, ARD_ANALOG);

	//Setup listeners for the input on the arduinoboard
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

void ofApp::analogPinChanged(const int& pin) {
	selector = ofMap(arduino.getAnalog(pinLerpPod), 0, 1023, 0, 2);
}

void ofApp::digitalPinChanged(const int& pin) {
	if (arduino.getDigital(pinButtonNormal) == 1) {
		map = 1;
		ofLog() << "Normal Map" << endl;
	}
	if (arduino.getDigital(pinButtonCar) == 1) {
		map = 2;
		ofLog() << "Car Map" << endl;
	}
	if (arduino.getDigital(pinButtonTrain) == 1) {
		map = 3;
		ofLog() << "Train Map" << endl;
	}
	if (arduino.getDigital(pinButtonPod) == 1) {
		map = 4;
		ofLog() << "Lerp Map" << endl;
	}
}

void ofApp::keyPressed(int key) {
	/*
	if (key == 'z' || key == 'Z') {
		map = 1;
		ofLog() << "Normal map" << endl;
	}
	if (key == 'x' || key == 'X') {
		map = 2;
		ofLog() << "Car map" << endl;
	}
	if (key == 'c' || key == 'C') {
		map = 3;
		ofLog() << "Train map" << endl;
	}
	if (key == 'v' || key == 'V') {
		map = 4;
		ofLog() << "Lerp Map" << endl;
	}
	*/
}

void ofApp::mouseMoved(int x, int y) {
	/*
	selector = ofMap(x, 20, ofGetWidth() - 20, 0, 2);
	*/
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

