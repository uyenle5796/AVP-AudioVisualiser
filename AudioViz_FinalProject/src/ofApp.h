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
        void audioOut(float * input, int bufferSize, int nChannels); //output audio to the speakers
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
    bool displayGui = true;
    ofxPanel gui;
    ofxFloatSlider angleDeg, rotateDeg, scaling;
    ofxFloatSlider colorVal;
    
    //EASYCAM
    ofEasyCam easyCam;
    
    
    //PHYLLOTAXIS SPIRAL
    float angle; //Divergence angle
    float r; //distance between the center of the capitulum and the center of the nth floret
    float n; //ordering number of the a floret, counting outward from the center
    float start = 0;
    
    //SUPERFORMULA
    
    
    //MAXIMILIAN
    maxiFFT myFFT;
    maxiSample sample;
    double sampleOut; //stores the output audio
    int sampleRate = 44100; //sampling rate
    float fftSize = 1024;
    int bufferSize = 512; //buffersize is Nyquist rate
    bool playAudio = true;
    int intensity = 20;
    
};
