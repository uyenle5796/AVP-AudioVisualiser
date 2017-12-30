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
        particles.push_back(i);
    }
}

//--------------------------------------------------------------
void Ring::setupGui() {
    
    parameters.setName("Ring");
    parameters.add(intensity.set("Intensity", 10, 10, 40));
    parameters.add(radius.set("Radius", 200, 100, 400));
    parameters.add(spacing.set("Spacing", 5, 1, 10));
    parameters.add(scale.set("Scale", 10, 5, 20));
    parameters.add(color.set("Colours", 255, 1, 350));
}

//--------------------------------------------------------------
void Ring::draw(float fftMagnitudes) {
    
    ofPushMatrix();
    ofTranslate(0, -100);
    ofRotateX(20); //tilt the shape a bin in x-axis
    ofRotateY(ofGetFrameNum());
    
    //Create the Circular shape by drawing 360 ellipses in 360 degrees
    for(int i=0; i < particles.size(); i += spacing) {
        
        //Set rainbow colours
        ofColor col;
        float hue = i + startColor;
        hue = i % int(color);
        col.setHsb(hue, 255, 255);
        ofSetColor(col);
        
        float posx = sin(i*scale) * (i / (i/radius));
        float posy = fftMagnitudes * intensity;
        float posz = cos(i*scale) * (i / (i/radius));
        
        ofDrawEllipse(posx, posy, posz, 5, 5);
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void Ring::update() {

}


