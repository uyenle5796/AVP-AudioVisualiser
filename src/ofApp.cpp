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
    
    /* SUPERFORMULA SETUP */
//    superformula = *new Superformula(ofGetWidth()/2, ofGetHeight()/2, 0);
//    superformula.setup();
    light.setDirectional();
    light.setOrientation(ofVec3f(0,60,60));
    
    ambientColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
    light.setAmbientColor(ambientColor);
    
    diffuseColor.set(255,0,0);
    light.setDiffuseColor(diffuseColor);
    
    mesh.enableColors();
    meshColor.set(ofRandom(255),ofRandom(255),ofRandom(255));

    /* GUI SETUP */
    gui.setup();
    
    //Phyllotaxis parameters
    gui.add(angleDeg.setup("Angle degree", 137.3, 137.0, 140.0));
    gui.add(rotateDeg.setup("Rotation degree", 0.3, 0.2, 0.5));
    gui.add(scaling.setup("Scaling", 8, 1, 10));
    gui.add(colorVal.setup("Colours", 300, 1, 360)); //Adjust colours
    
    //Superformula parameters
//    gui.add(superformula.parameters);
    gui.add(a1value.setup("a1value", 1,0,5));
    gui.add(a2value.setup("a2value", 1,0,5));
    gui.add(n1value.setup("n1value", 8,0,40));
    gui.add(n2value.setup("n2value", 1,0,5));
    gui.add(n3value.setup("n3value", 1,0,5));
    gui.add(n4value.setup("n4value", 1,0,5));
    gui.add(numpoints.setup("numpoints", 0.05,0.02,0.2));
    gui.add(drawWire.setup("Draw Wireframe", false));
    gui.add(drawPoints.setup("Draw Points", false));
    
    /* MAXIMILIAN SETUP */
    //Setup FFT
    myFFT.setup(fftSize, 512, 256);
    
    // Load samples from files
    sample.load(ofToDataPath("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AudioViz_FinalProject/bin/data/lemoncreme_piano.wav"));
    
    //Setup the audio output
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4); /* Call this last ! */
}

//---------------------------------------------------------------------
ofVec3f ofApp::sf3d(float x, float y) {
    
    float i = -PI + x*numpoints;
    float j = -PI/2.0 + y*numpoints;
    
    float raux1 = pow(abs(1/a1value*abs(cos(n1value * i/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*i/4))),n4value);
    
    float r1 = pow(abs(raux1),(-1/n2value));
    float raux2 = pow(abs(1/a1value*abs(cos(n1value*j/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*j/4))),n4value);
    float r2 = pow(abs(raux2),(-1/n2value));
    
    float posx = r1*cos(i)*r2*cos(j)*100.0f;
    float posy = r1*sin(i)*r2*cos(j)*100.0f;
    float posz = r2*sin(j)*100.0f;
    
    return ofVec3f(posx, posy, posz);
}

//---------------------------------------------------------------------
void ofApp::moveVertices() {
    int numVerts = mesh.getNumVertices();
    
    for (int i=0; i < numVerts; i++) {
        ofVec3f vert = mesh.getVertex(i);
        
        //Move vertices in z axis along with the audio amplitudes
        for(int j=0; j < bufferSize; j++) {
            vert.z += myFFT.magnitudes[j];
        }
        mesh.setVertex(i, vert);
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    
    /* PHYLLOTAXIS */
    //Make the shape grow by adding one floret every frame.
    //However this makes the the program slows down significant when 'n' gets too large. So I added a limit so the shape stops growing at 500 florets to maintain performance.
    if (n <= 500)
        n ++;
    //cout << n << endl;
    
    //Increment colours to create rainbow effect
    start += scaling;
    
    /* SUPERFORMULA */
//    superformula.update();
    mesh.clear();
    int N_X = ceil((2.0*PI) / numpoints);
    int N_Y = ceil(PI / numpoints);
    
    for(int x=0;x<N_X;x++) {
        for(int y=0;y<N_Y;y++) {
            mesh.addVertex(sf3d(x,y));
            mesh.addColor(ofColor(meshColor));
        }
    }
    mesh.addVertex(sf3d(PI/numpoints,PI/numpoints));
    mesh.addColor(ofColor(meshColor));
    
    lastRow.clear();
    
    for(int x=0;x<N_X;x++) {
        for(int y=0;y<N_Y-1;y++) {
            
            if(x == N_X-1) {
                
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = y+1;
                int idx4 = y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
            } else {
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = (x+1)*N_Y+y+1;
                int idx4 = (x+1)*N_Y+y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
                if(y == N_Y-2) {
                    lastRow.push_back(idx2);
                }
            }
            
        }
    }
    int lastVertex = mesh.getNumVertices()-1;
    
    for(int i=0;i<lastRow.size()-1;i++) {
        mesh.addTriangle(lastRow[i], lastRow[i+1], lastVertex);
    }
    mesh.addTriangle(lastRow[0],lastRow[lastRow.size()-1], lastVertex);
    
    ofxMeshUtils::calcNormals(mesh);
    
    moveVertices();

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
    }
    
    /* SUPERFORMULA */
//    superformula.draw();
    if (showSuperformula) {
        ofPushMatrix();
        glShadeModel(GL_FLAT);
        glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
        
        if(!drawPoints) {
            ofDisableAlphaBlending();
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            glEnable(GL_DEPTH_TEST);
            ofEnableLighting();
            light.enable();
            mesh.draw();
            light.disable();
            ofDisableLighting();
        } else {
            mesh.setMode(OF_PRIMITIVE_POINTS);
            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_PROGRAM_POINT_SIZE_ARB);
            glPointSize(1.5f); //vertex size
            mesh.clearColors();
            
            //TO DO Set rainbow colours to the vertices
            int col = 0;
            col++;
            float hue = col % 255;
            ofColor vertexColor;
            
            vertexColor.setHsb(hue, 255, 255);
            ofSetColor(vertexColor); //vertex color
            ofEnableAlphaBlending();
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            
            mesh.draw();
        }

        if(drawWire) {
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            mesh.clearColors();
            ofSetColor(255,255,255,100); //white
            mesh.drawWireframe();
        }
        glDisable(GL_DEPTH_TEST);
        ofPopMatrix();
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
    
//    superformula.keyPressed(key);
    
    if(key == 'r') {
        meshColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
        ambientColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
        diffuseColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
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
