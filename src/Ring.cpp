//
//  Ring.cpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 30/12/2017.
//

#include "Ring.hpp"

Ring::Ring() {
    
    //Create an array of 360 particles
    for(int i=0; i < 360; i++) {
        points.push_back(i);
    }
}

//--------------------------------------------------------------
void Ring::setupGui() {
    
    parameters.setName("Ring");
    parameters.add(intensity.set("Intensity", 10, 10, 40));
    parameters.add(radius.set("Radius", 200, 100, 400));
    parameters.add(spacing.set("Spacing", 5, 1, 10));
    parameters.add(R.set("Red", 255, 1, 350));
    parameters.add(G.set("Green", 100, 1, 255));
    parameters.add(B.set("Blue", 222, 1, 255));
}

//--------------------------------------------------------------
void Ring::draw(float fftMagnitudes) {
    
    ofPushMatrix();
    ofTranslate(0, -100); //move it a bit down
    ofRotateX(20); //tilt the shape a bit in x-axis so it faces towards the user
    ofRotateY(ofGetFrameNum()); //rotate the shape in Y-axis according to frame rate
    
    //Create the Circular shape by drawing 360 ellipses in 360 degrees
    for(int i=0; i < points.size(); i += spacing) {
        
        //Set rainbow colours
        float red = i + startColor;
        red = i % int(R);
        ofSetColor(red, G, B);
        
        //The below code was adapted from 'Spiral circle' of https://github.com/soniaboller/soniaboller.github.io/tree/master/audible-visuals
        
        float posx = sin(i) * (i / (i/radius));
        float posy = fftMagnitudes * intensity; //move the points in y-axis along with the music, scaled with an intensity
        float posz = cos(i) * (i / (i/radius));
        
        ofDrawEllipse(posx, posy, posz, 5, 5);
    }
    
    ofPopMatrix();
}


