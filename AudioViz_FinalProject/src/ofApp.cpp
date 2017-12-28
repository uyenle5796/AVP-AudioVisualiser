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
    
    //GUI SETUP
    gui.setup();
    gui.add(degree.setup("Angle degree", 137.3, 137.0, 140.0));
    
    // MAXIMILIAN SETUP
    //Setup FFT
    myFFT.setup(fftSize, 512, 256);
    
    // Load samples from files
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
    
    //GUI and INSTRUCTIONS
    if(displayGui) {
        gui.draw();
    }
    
    //PHYLLOTAXIS
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(n * 0.3);
    
    for (int i = 0; i < n; i++) {
        float angle = i * degree;
        float radius = c * sqrt(i);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        
        float hu = i + start;
        hu = i/3 % 360;
        
        ofSetColor(255); //hu, 255, 255
        ofDrawEllipse(x, y, 3, 3);
    }
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
    
    //USER INTERACTIONS
    //G to hide/show Gui
    if(key == 'G') {
        displayGui = !displayGui;
    }
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
