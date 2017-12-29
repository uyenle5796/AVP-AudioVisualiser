#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maximilian.h"
#include "ofxGui.h"
//#include "Superformula.hpp"
#include "ofxMeshUtils.h"

using namespace std;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void audioOut (float *output, int bufferSize, int nChannels);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    /* GUI */
    bool displayGui = true;
    bool showPhyllotaxis = false;
    bool showSuperformula = true;
    
    //Phyllotaxis GUI parameters
    ofxPanel gui;
    ofxFloatSlider angleDeg, rotateDeg, scaling;
    ofxFloatSlider colorVal;
    
    //Superformula GUI parameters
    ofxFloatSlider a1value, a2value;
    ofxFloatSlider n1value, n2value, n3value, n4value;
    ofxFloatSlider stepvalue;
    ofxToggle drawWire, drawPoints;
    
    /* EASYCAM */
    ofEasyCam easyCam;
    
    /* VISUALISATION PATTERNS */
    //PHYLLOTAXIS
    float angle; //Divergence angle
    float r; //distance between the center of the capitulum and the center of the nth floret
    float n; //ordering number of the a floret, counting outward from the center
    float start = 0;
    
    //SUPERFORMULA
//    Superformula superformula;
    float n1target, n2target, n3target, n4target,a1target,a2target;
    ofMesh mesh;
    ofVec3f sf3d(float x, float y);
    vector<int> lastRow;
    ofLight light;
    
    /* MAXIMILIAN */
    maxiFFT myFFT;
    maxiSample sample;
    double sampleOut; //stores the output audio
    int sampleRate = 44100; //sampling rate
    float fftSize = 1024;
    int bufferSize = 512; //buffersize is Nyquist rate
    bool playAudio = true;
    int intensity = 20;
    
};
