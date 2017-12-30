#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Final Project: Audio Visualiser

 An Audio Visualiser with Phyllotaxis, Superformula and Ring shapes.
 
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
    ofSetFullscreen(true);
    
    /* VISUALISERS SETUP */
    superformula = *new Superformula();
    phyllotaxis = *new Phyllotaxis();
    ring = *new Ring();

    /* GUI SETUP */
    gui.setup();
    
    //Phyllotaxis GUI
    phyllotaxis.setupGui();
    gui.add(phyllotaxis.parameters);
    
    //Superformula GUI
    superformula.setupGui();
    gui.add(superformula.parameters);

    //Ring GUI
    ring.setupGui();
    gui.add(ring.parameters);
    
    /* MAXIMILIAN SETUP */
    //Setup FFT
    myFFT.setup(fftSize, 512, 256);
    
    // Load samples from files
    pianoSample.load(ofToDataPath("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AudioViz_FinalProject/bin/data/lemoncreme_piano.wav"));
    drumSample.load(ofToDataPath("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AudioViz_FinalProject/bin/data/stezzer-102-break.wav"));
    
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
        
        ofSetColor(255, 200);
        ofDrawBitmapString("1,2,3: change design", 20, ofGetHeight()-70);
        ofDrawBitmapString("5,6: change audio", 20, ofGetHeight()-55);
        ofDrawBitmapString("G: show/hide Gui", 20, ofGetHeight()-40);
        ofDrawBitmapString("F: exit fullscreen", 20, ofGetHeight()-25);
        ofDrawBitmapString("SPACE: play/pause audio", 20, ofGetHeight()-10);
    }
    
    //Start EasyCam - allows changing camera point of view
    easyCam.begin();
    
    /* PHYLLOTAXIS */
    if(showPhyllotaxis) {
        for(int i=0; i < bufferSize; i++) {
            phyllotaxis.draw(myFFT.magnitudes[i]);
        }
    }
    
    /* SUPERFORMULA */
    if (showSuperformula)
        superformula.draw();
    
    /* RING */
    if (showRing) {
        for(int i=0; i < bufferSize; i++) {
            ring.draw(myFFT.magnitudes[i]);
        }
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
            if(playPianoSample)
                sampleOut = pianoSample.play(); //replay the sample once it's ended
            if (playDrumSample)
                sampleOut = drumSample.play();

            // Assign audio output to both channels of the speaker
            output[i*nChannels    ] = sampleOut; //left channel
            output[i*nChannels + 1] = sampleOut; //right channel
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // USER INTERACTIONS
    
    //1 to show Phyllotaxis shape
    if(key == '1') {
        showPhyllotaxis = true;
        showSuperformula = false;
        showRing = false;
    }
    
     //2 to show Superformula shape
    if(key == '2') {
        showSuperformula = true;
        showPhyllotaxis = false;
        showRing = false;
    }
    superformula.keyPressed(key); //Use Superformula key interactions
    
    //3 to show Ring shape
    if(key == '3') {
        showRing = true;
        showPhyllotaxis = false;
        showSuperformula = false;
    }
    
    //5 to play pianoSample
    if(key == '5') {
        playPianoSample = true;
        playDrumSample = false;
    }
    
    //6 to play drumSample
    if(key == '6') {
        playPianoSample = false;
        playDrumSample = true;
    }

    //General interactions
    if(key == 'g') displayGui = !displayGui; //'g' to hide/show Gui
    if(key == ' ') playAudio = !playAudio; //SPACE to pause/play audio
    if(key == 'f') ofSetFullscreen(false); //'f' to exit fullscreen
    
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
