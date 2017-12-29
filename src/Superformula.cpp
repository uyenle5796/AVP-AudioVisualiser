//
//  Superformula.cpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 29/12/2017.
//

#include "Superformula.hpp"

Superformula::Superformula(float posx, float posy, float posz): mPosx(posx), mPosy(posy), mPosz(posz) {
    
    //Setup directional, ambient and diffuse lights
    light.setDirectional();
    light.setOrientation(ofVec3f(0,60,60));
    
    ambientColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
    light.setAmbientColor(ambientColor);
    
    diffuseColor.set(255,0,0);
    light.setDiffuseColor(diffuseColor);
    
    mesh.enableColors();
    meshColor.set(ofRandom(255),ofRandom(255),ofRandom(255));
}

//--------------------------------------------------------------
void Superformula::setupPanel(string name) {

}

//--------------------------------------------------------------
ofVec3f Superformula::sf3d(float x, float y) {
    
}

//--------------------------------------------------------------
void Superformula::draw() {

}

//--------------------------------------------------------------
void Superformula::update() {
  
}

//--------------------------------------------------------------
void Superformula::keyPressed(int key) {
    
}
