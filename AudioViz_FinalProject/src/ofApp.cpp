#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Final Project: Audio Visualiser
 
 by Uyen Le
 tle004@gold.ac.uk
 
 ----------------
Audio visualiser with Phyllotaxis Spiral and Superformula using Maximilian.
 */

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetFullscreen(true);
    ofSetVerticalSync(true);
    
    //GUI SETUP
    gui.setup();
    //Adjust Phyllotaxis parameters
    gui.add(angleDeg.setup("Angle degree", 137.3, 137.0, 140.0));
    gui.add(rotateDeg.setup("Rotation degree", 0.3, 0.2, 0.5));
    gui.add(scaling.setup("Scaling", 7, 1, 10));
    
    //Adjust colours
    gui.add(colorVal.setup("Color Value", 360, 1, 360));
    
    // MAXIMILIAN SETUP
    //Audio inputs and outputs
//    lAudioOut = new float[bufferSize];/* outputs */
//    rAudioOut = new float[bufferSize];
//    lAudioIn = new float[bufferSize];/* inputs */
//    rAudioIn = new float[bufferSize];
//
//    memset(lAudioOut, 0, bufferSize * sizeof(float));
//    memset(rAudioOut, 0, bufferSize * sizeof(float));
//    memset(lAudioIn, 0, bufferSize * sizeof(float));
//    memset(rAudioIn, 0, bufferSize * sizeof(float));
    
    //Setup FFT
    myFFT.setup(fftSize, 512, 256);
    
    // Load samples from files
    sample.load(ofToDataPath("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AudioViz_FinalProject/bin/data/lemoncreme_piano.wav"));
    
    //Setup the audio output
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4); /* Call this last ! */
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
        ofDrawBitmapString("'1' to show/hide GUI", 20, ofGetHeight()-25);
        ofDrawBitmapString("SPACE to play/pause audio", 20, ofGetHeight()-10);
    }
    
    easyCam.begin();
    
    //PHYLLOTAXIS
    ofRotate(n * rotateDeg);
    
    for (int i = 0; i < n; i++) {
        angle = i * angleDeg;
        r = scaling * sqrt(i);
        float x = r * cos(angle);
        float y = r * sin(angle);
        
        //Set rainbow colours
        ofColor color;
        float hue = i + start;
        hue = i % int(colorVal);
        color.setHsb(hue, 255, 255);
        ofSetColor(color);
        
        //Take amplitudes of the audio sample using FFT and assign it to z values of each floret
        //so that the floret moves in z axis along with the audio amplitudes
        for(int j=0; j < bufferSize; j++) {
            float z = myFFT.magnitudes[j] * intensity;
            
            ofDrawEllipse(x, y, z, 3, 3);
        }
    }
    
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::audioOut (float *output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++) {
        
        if (myFFT.process(sampleOut)) {
            myFFT.magsToDB(); //get the amplitude in Decibels
        }
        
        //Store the audio sample to sampleOut
        if (playAudio) {
            sampleOut = sample.playOnce(); //play the sample once
            
            // Assign audio output to both channels of the speaker
            output[i*nChannels    ] = sampleOut; //left channel
            output[i*nChannels + 1] = sampleOut; //right channel
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //USER INTERACTIONS
    //1 to hide/show Gui
    if(key == '1')
        displayGui = !displayGui;

    //SPACE to pause/play audio
    if(key == ' ')
        playAudio = !playAudio;
    
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
