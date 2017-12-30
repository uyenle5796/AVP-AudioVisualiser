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
    ofTranslate(0, -100);
    ofRotateX(20); //tilt the shape a bin in x-axis
    ofRotateY(ofGetFrameNum());
    
    //Create the Circular shape by drawing 360 ellipses in 360 degrees
    for(int i=0; i < points.size(); i += spacing) {
        
        //Set rainbow colours
        float red = i + startColor;
        red = i % int(R);
        ofSetColor(red, G, B);
        
        float posx = sin(i) * (i / (i/radius));
        float posy = fftMagnitudes * intensity;
        float posz = cos(i) * (i / (i/radius));
        
        ofDrawEllipse(posx, posy, posz, 5, 5);
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void Ring::update() {

}


