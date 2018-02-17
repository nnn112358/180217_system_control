#include "ofApp.h"

void RungeKutta(MatrixXd dX, MatrixXd &X, MatrixXd u, double tt, double dt, MatrixXd A, MatrixXd B, MatrixXd C, MatrixXd D) {
	MatrixXd k1 = A*X + B*u;
	MatrixXd k2 = A*(X + 0.5*k1*dt) + B*u;
	MatrixXd k3 = A*(X + 0.5*k2*dt) + B*u;
	MatrixXd k4 = A*(X + k3*dt) + B*u;
	MatrixXd k = (k1 + 2.0*k2 + 2.0*k3 + k4)*dt / 6.0;
	X = X + k;
}
void ofApp::setup(){
	ofSetVerticalSync(true); // sync with vertical refresh rate
	ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);

	graph.setup(100, 100, 800, 400);
	graph.setName("spring-mass-damper system wave");     // it automatically loads setting file, (sample.xml)
	graph.setDx(2.0); // which means delta of time
	graph.setColor(ofColor::white);  // ofColor(255,255,255)
	graph.setBufSize(300);  
	graph.setLabel({ "y0","u" });

	frame = 0;

	gui.setup("parametor");
	gui.add(kk.setup("K", 1.0, 0.0, 5.0));
	gui.add(mm.setup("M", 0.1, 0.0, 1.0));
	gui.add(cc.setup("C", 0.1, 0.0, 1.0));
	gui.add(save_img.set("save_img", true));
	AA.resize(2, 2);
	AA << 0, 1, -kk / mm, -cc / mm;

	BB.resize(2, 1);
	BB << 1, 1 / mm;

	CC.resize(1, 2);
	CC << 1, 0;

	DD.resize(1, 1);
	DD << 1;

	XX.resize(2, 1);
	XX(0, 0) = 10;
	XX(1, 0) = 0;
	dXX.resize(2, 1);
	dXX(0, 0) = 0;
	dXX(1, 0) = 0;

	uu.resize(1, 1);
	uu << 0;
	YY.resize(1, 1);
	YY(0, 0) = 0;


	dt = 0.01;
	tt = 0.0;
}

//--------------------------------------------------------------
void ofApp::update() {
	frame++;



	if (save_img) {
		if (pic_frame % 5 == 0) {
			img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			char moji[1024];
			sprintf_s(moji, "img\\img_%05d.png", pic_frame);
			img.save(moji, OF_IMAGE_QUALITY_HIGH);
		}
	}
	pic_frame++;

	AA << 0, 1, -kk / mm, -cc / mm;
	BB << 1, 1 / mm;

	double TT = 100.0;

	uu(0, 0) = ofRandom(-10,10);

	RungeKutta(dXX, XX, uu, tt, dt, AA, BB, CC, DD);
	
	YY = CC*XX;
	tt += dt;

	vector<float>value;
	value.push_back(YY(0, 0));

	value.push_back(uu(0,0));

	graph.add(value);

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(50, 50, 50);
	gui.draw();

	graph.draw();

}

//--------------------------------------------------------------

