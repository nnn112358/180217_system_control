#pragma once

#include "ofMain.h"
#include "ofxGraph.h"
#include "ofxGui.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Eigen/Dense"
#include "Eigen/Core"
#include <iostream>
#include <fstream>

using namespace Eigen;
using namespace std;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		ofxGraph graph;
		long frame;
		ofxPanel gui;
		ofxFloatSlider kk,mm,cc;
		MatrixXd AA;
		MatrixXd BB; 
		MatrixXd CC;
		MatrixXd DD;
		MatrixXd XX;
		MatrixXd dXX;
		MatrixXd uu;
		MatrixXd YY;
		double dt ;
		double tt ;


		ofParameter<bool> save_img;
		ofImage   img;
		int pic_frame;

};
