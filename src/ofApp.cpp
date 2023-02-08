#include "ofApp.h"
#include <fstream>
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(255);
}

//--------------------------------------------------------------
void ofApp::update() {
	// update grid size in case of window resizing
	gridSizeY = static_cast<double>(ofGetHeight()) / rows;
	gridSizeX = static_cast<double>(ofGetWidth()) / columns;
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(0);
	drawPixels(image, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key == 's') {
		saveImage(image);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	for (int n{ 0 }; n < rows; n++) {
		for (int m{ 0 }; m < columns; m++) {
			const double lowerYBound{ gridSizeY * n };
			const double lowerXBound{ gridSizeX * m };
			const double upperYBound{ lowerYBound + gridSizeY };
			const double upperXBound{ lowerXBound + gridSizeX };

			// update grid pixel
			if (x > lowerXBound && x < upperXBound &&
				y > lowerYBound && y < upperYBound) {
				image[n][m] = !image[n][m];
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::drawPixels(std::vector<std::vector<bool>> pixels, double width, double height) {
	for (int n{ 0 }; n < rows; n++) {
		for (int m{ 0 }; m < columns; m++) {
			const double lowerYBound{ gridSizeY * n };
			const double lowerXBound{ gridSizeX * m };

			// draw grid
			ofDrawLine(0, lowerYBound, width, lowerYBound);
			ofDrawLine(lowerXBound, 0, lowerXBound, height);

			// draw pixel
			if (pixels[n][m]) {
				ofDrawRectangle(lowerXBound, lowerYBound, gridSizeX, gridSizeY);
			}
		}
	}
}


void ofApp::loadImage() {
	const std::string fileName{ "pixelArt.pmm" };
	std::ifstream inputFile{ fileName, std::ios_base::in };
	std::string fileType;

	// Handle header
	// get file type
	if (inputFile) {
		std::cout << "The " << fileName << " file opened successfully!\n";
		// get ppm type
		inputFile >> fileType;
	}
	else {
		std::cout << "The was an issue opening the " << fileName << " file.\n";
	}
	// get file dimensions
	bool isColumnCountFound = false;
	bool isRowCountFound = false;
	while (!inputFile.eof() || !isColumnCountFound && !isRowCountFound) {
		std::string data;
		inputFile >> data;
		if (data == "#") {
			// skip the rest of the line
			std::getline(inputFile, data);
		} else if (!isColumnCountFound) {
			columns = stoi(data);
			isColumnCountFound = true;

		} else if (isColumnCountFound && !isRowCountFound) {
			rows = stoi(data);
			isRowCountFound = true;
		}
	}
	if(!isColumnCountFound || !isRowCountFound) {
		std::cout << "Incorrect header format. The image dimensions could not be found";
	}
	
	if(!inputFile.eof()) {
		image.resize(rows, std::vector<bool>(columns, false));
		std::vector<bool> data{ std::istream_iterator<bool>{inputFile}, {} };
		int dataIndex = 0;
		for (int n{ 0 }; n < rows; n++) {
			for (int m{ 0 }; m < columns; m++) {
				image[n][m] = data[dataIndex++];
			}
		}
	}
}


void ofApp::saveImage(std::vector<std::vector<bool>> pixels) {
	std::ofstream outputFile{ "pixelArt.ppm" };
	outputFile << "P1\n";
	outputFile << columns << " " << rows << "\n";
	for (int n{ 0 }; n < rows; n++) {
		for (int m{ 0 }; m < columns; m++) {
			outputFile << pixels[n][m];
			// append a new line if current pixel is at the last column
			// otherwise append a space
			if(m == columns - 1) {
				outputFile << "\n";
			} else {
				outputFile << " ";
			}
		}
	}
	outputFile.close();
}