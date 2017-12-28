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
}

//--------------------------------------------------------------
void ofApp::update(){
    n += 5;
    start += 5;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //PHYLLOTAXIS
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(n * 0.3);
    
    for (int i = 0; i < n; i++) {
        float a = i * 137.6; //137.3, 137.6
        float r = c * sqrt(i);
        float x = r * cos(a);
        float y = r * sin(a);
        
        float hu = i + start;
        hu = i/3 % 360;
        
        ofSetColor(255); //hu, 255, 255
        ofDrawEllipse(x, y, 3, 3);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
