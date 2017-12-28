#include "ofApp.h"

/*
 
 Advanced Audio-Visual Processing Coursework
 Final Project: Audio Visualiser
 
 by Uyen Le
 tle004@gold.ac.uk
 
 ----------------
 An Audio Visualiser with Phyllotaxis and Archimedean spiral usin Maximilian library.
 
 ----------------
 Credits:
 - Phyllotaxis tutorial: https://www.youtube.com/watch?v=KWoJgHFYWxY
 */

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableSmoothing();
    
    //MAXIMILIAN SETUP
    myFFT.setup(fftSize, 512, 256);
    
    //Load audio from files
    sample.load(ofToDataPath("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AudioViz_FinalProject/bin/data/lemoncreme_piano.wav"));
    
    //Setup the audio output
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,0,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    n += 5;
    start += 5;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    easyCam.begin();
    
    /*** INSTRUCTIONS TEXT ***/
    if (displayInstructions) {
        ofDrawBitmapString("1,2,3 to change degree", 20, 20);
        ofDrawBitmapString("SPACE to pause/play audio", 20, 35);
        ofDrawBitmapString("A to hide/show instructions", 20, 50);
    }
    
    /**** PHYLLOTAXIS ****/
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(n * 0.3);
    
    for (int i = 0; i < n; i++) {
        float a = i * degree;
        float r = c * sqrt(i);
        float x = r * cos(a);
        float y = r * sin(a);
        
        float hu = i + start;
        hu = i/3 % 360;
        
        ofSetColor(hu, 255, 255);
        ofDrawEllipse(x, y, 3, 3);
    }
    
    /**** ARCHIMEDIAN SPIRAL ****/
    
//    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::audioOut (float *output, int bufferSize, int nChannels) {

    for (int i = 0; i < bufferSize; i++) {
        
        if (myFFT.process(sampleOut)) {
            //stuff
        }
        
        // Assign audioOoutputAudiout to both channels of the speaker
        output[i*nChannels    ] = sampleOut; //left channel
        output[i*nChannels + 1] = sampleOut; //right channel
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // USER INTERACTIONS
    
    //Press 1,2,3 to change Phyllotaxis degree
    if(key == '1')
        degree = 137.3;
    if(key == '2')
        degree = 137.5;
    if(key == '3')
        degree = 137.6;
    
    //Press A to hide/show instructions
    if(key == 'A')
        displayInstructions = !displayInstructions;
    
    //SPACE to pause/play audio
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
