#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Final Project: Audio Visualiser
 
 by Uyen Le
 tle004@gold.ac.uk
 
 ----------------
Audio visualiser with Phyllotaxis and Archimedean Spiral using Maximilian.
 */

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    

    //GUI SETUP
    gui.setup();
    gui.add(angleDeg.setup("Angle degree", 137.3, 137.0, 140.0));
    gui.add(rotateDeg.setup("Rotation degree", 0.3, 0.2, 0.5));
    gui.add(scaling.setup("Scaling", 5, 1, 10));
    
    
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
    n += scaling;
    start += scaling;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //GUI and INSTRUCTIONS
    if(displayGui) {
        gui.draw();
        
        ofSetColor(255);
        ofDrawBitmapString("'1' to show/hide GUI", 20, 110);
    }
    
    //PHYLLOTAXIS
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(n * rotateDeg);
    
    for (int i = 0; i < n; i++) {
        angle = i * angleDeg;
        r = scaling * sqrt(i);
        float x = r * cos(angle);
        float y = r * sin(angle);
        
        float hue = i + start;
        hue = i/3 % 360;
        ofColor color = ofColor::fromHsb(hue, 255, 255);
        ofSetColor(color); //hu, 255, 255
        
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
    //1 to hide/show Gui
    if(key == '1')
        displayGui = !displayGui;

    //SPACE to pause/play audio
//    if(key == ' ')
//        playAudio = !playAudio;
    
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
