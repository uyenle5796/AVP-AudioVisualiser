#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maximilian.h"
#include "ofxGui.h"
#include "ofxMeshUtils.h"
#include "Phyllotaxis.hpp"
#include "Superformula.hpp"
#include "Ring.hpp"


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
    
    /* EASYCAM */
    ofEasyCam easyCam;
    
    /* GUI */
    ofxPanel gui;
    bool displayGui = true;
    bool showPhyllotaxis = true;
    bool showSuperformula = false;
    bool showRing = false;
    
    /* VISUALISERS */
    Phyllotaxis phyllotaxis;
    Superformula superformula;
    Ring ring;
    
    /* MAXIMILIAN */
    maxiFFT myFFT;
    maxiSample pianoSample, drumSample;
    
    double sampleOut; //stores the output audio
    int sampleRate = 44100; //sampling rate
    float fftSize = 1024;
    int bufferSize = 512; //buffersize is Nyquist rate
    
    bool playAudio = true;
    bool playPianoSample = true;
    bool playDrumSample = false;
    
};


