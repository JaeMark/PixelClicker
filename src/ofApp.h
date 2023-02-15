#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	int rows{ 9 };
	int columns{ 9 };
	double gridSizeY{ static_cast<double>(ofGetHeight()) / rows };
	double gridSizeX{ static_cast<double>(ofGetWidth()) / columns };

	// initialize a matrix of false Booleans to store the grid drawing
	std::vector<std::vector<bool>> image{ static_cast<vector<vector<bool>>::size_type>(rows),  std::vector<bool>(columns, false) };

	void drawPixels(std::vector<std::vector<bool>> pixels, double width, double height);
	void saveImage(std::vector<std::vector<bool>> pixels) const;
	void loadImage();
};

