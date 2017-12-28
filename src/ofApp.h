#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maximilian.h"
#include "ofxGui.h"

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
    
    //GUI and INSTRUCTIONS
    bool displayInstructions = true;
    ofxPanel gui;
    
    //EASYCAM
    ofEasyCam easyCam; //allows looking around
    
    //PHYLLOTAXIS
    float degree = 137.3;
    float n;
    float c = 5;
    float start = 0;
    
    //ARCHIMEDIAN SPIRAL
    
    
    //MAXIMILIAN
    maxiFFT myFFT;
    
    //Audio samples
    maxiSample sample;
    
    //Variables
    double sampleOut; //stores the output audio
    int sampleRate = 44100;
    float fftSize = 1024;
    int bufferSize = 512;
    
};
