#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Final Project: Audio Visualiser

 An Audio Visualiser with Phyllotaxis spiral and Superformula using Maximilian library.
 
 ----------------
 by Uyen Le
 tle004@gold.ac.uk
 */

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);
    ofSetFullscreen(false);
    
    /* VISUALISERS SETUP */
    superformula = *new Superformula();
    phyllotaxis = *new Phyllotaxis();

    /* GUI SETUP */
    gui.setup();
    gui.add(phyllotaxis.parameters); //Phyllotaxis GUI
    gui.add(superformula.parameters); //Superformula GUI
    
    /* MAXIMILIAN SETUP */
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
    
    /* PHYLLOTAXIS */
    if (showPhyllotaxis) {
        phyllotaxis.update();
    }
    
    /* SUPERFORMULA */
    if (showSuperformula) {
        superformula.update();
        
        //Move each vertex in z axis along with the audio amplitudes
        for(int i=0; i < bufferSize; i++) {
            superformula.moveVertices(myFFT.magnitudes[i]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* GUIs and INSTRUCTIONS */
    if(displayGui) {
        gui.draw();
        
        ofSetColor(255);
        ofDrawBitmapString("1,2,3 to change design", 20, ofGetHeight()-70);
        ofDrawBitmapString("G to show/hide Gui", 20, ofGetHeight()-50);
        ofDrawBitmapString("F to exit fullscreen", 20, ofGetHeight()-30);
        ofDrawBitmapString("SPACE to play/pause audio", 20, ofGetHeight()-10);
    }
    
    //Start EasyCam - allows changing camera point of view
    easyCam.begin();
    
    //PHYLLOTAXIS
    if(showPhyllotaxis) {
        for(int i=0; i < bufferSize; i++) {
            phyllotaxis.draw(myFFT.magnitudes[i]);
        }
    }
    
    /* SUPERFORMULA */
    if (showSuperformula) {
        superformula.draw();
    }
    
    easyCam.end(); //End EasyCam
}

//--------------------------------------------------------------
void ofApp::audioOut (float *output, int bufferSize, int nChannels) {

    for (int i = 0; i < bufferSize; i++) {
        
        if (myFFT.process(sampleOut)) {
            myFFT.magsToDB(); //get the amplitude in Decibels
        }
        
        //Play the audio sample and store it to sampleOut
        if (playAudio) {
            sampleOut = sample.play(); //replay the sample once it's ended
            
            // Assign audio output to both channels of the speaker
            output[i*nChannels    ] = sampleOut; //left channel
            output[i*nChannels + 1] = sampleOut; //right channel
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // USER INTERACTIONS
    if(key == '1') {
        showPhyllotaxis = true; //1 to show Phyllotaxis shape
        showSuperformula = false;
    }
    if(key == '2') {
        showPhyllotaxis = false; //2 to show Superformula shape
        showSuperformula = true;
    }
    superformula.keyPressed(key); //Use Superformula key interactions

//    if(key == '3') {
//        showPhyllotaxis = false; //3 to show ??? shape
//        showSuperformula = true;
//    }
    
    if(key == 'g')
        displayGui = !displayGui; //1 to hide/show Gui
    if(key == ' ')
        playAudio = !playAudio; //SPACE to pause/play audio
    if(key == 'f')
        ofSetFullscreen(false); //'f' to exit fullscreen
    
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
