#include "ofApp.h"

/*
 Advanced Audio-Visual Processing Coursework
 Final Project: Audio Visualiser
 
 by Uyen Le
 tle004@gold.ac.uk
 
 ----------------
 An Audio Visualiser with Phyllotaxis and Archimedean spiral using Maximilian library.
 */

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    //ofSetSmoothLighting(true);
    ofSetFullscreen(false);
    
    /* GUI SETUP */
    gui.setup();
    
    //Adjust Phyllotaxis parameters
    gui.add(angleDeg.setup("Angle degree", 137.3, 137.0, 140.0));
    gui.add(rotateDeg.setup("Rotation degree", 0.3, 0.2, 0.5));
    gui.add(scaling.setup("Scaling", 8, 1, 10));
    gui.add(colorVal.setup("Colours", 300, 1, 360)); //Adjust colours
    
    //Adjust Superformula parameters
    
    
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
    //Make the shape grow by adding one floret every frame.
    //However this makes the the program slows down significant when 'n' gets too large. So I added a limit so the shape stops growing at 500 florets to maintain performance.
    if (n <= 500)
        n ++;
    //        cout << n << endl;
    start += scaling;
}

//--------------------------------------------------------------
void ofApp::draw(){
    /* GUIs and INSTRUCTIONS */
    if(displayGui) {
        gui.draw();
        
        ofSetColor(255);
        ofDrawBitmapString("'1' to show/hide GUI", 20, ofGetHeight()-50);
        ofDrawBitmapString("SPACE to play/pause audio", 20, ofGetHeight()-30);
        ofDrawBitmapString("F to exit fullscreen", 20, ofGetHeight()-10);
    }
    
    //Start EasyCam - allows changing camera point of view
    easyCam.begin();
    
    glEnable(GL_DEPTH_TEST);
    
    //PHYLLOTAXIS
    ofPushMatrix();
    ofRotate(n * rotateDeg);
    
    //Draw the Phyllotaxis spiral shape using a for loop, where 'n' increments by 5 every frame (in update). This makes the shape grow bigger.
    for (int i = 0; i < n; i++) {
        
        //Create the Phyllotaxis pattern based on the mathematical formula
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
        
        //Assign amplitudes of the audio sample using FFT and assign it to z values of each floret
        //so that the floret moves in z axis along with the audio amplitudes
        for(int j=0; j < bufferSize; j++) {
            float z = myFFT.magnitudes[j] * intensity; //scale up the magnitudes by multiplying with a value to make the effect easier to see
            
            ofDrawEllipse(x, y, z, 3, 3);
        }
    }
    ofPopMatrix();
    
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
            sampleOut = sample.play();
            
            // Assign audio output to both channels of the speaker
            output[i*nChannels    ] = sampleOut; //left channel
            output[i*nChannels + 1] = sampleOut; //right channel
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // USER INTERACTIONS
    if(key == '1')
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
