//
//  Superformula.hpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 29/12/2017.
//

#ifndef Superformula_hpp
#define Superformula_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMeshUtils.h"

class Superformula {
    
public:
    
    //Lights
    ofLight light;
    ofColor meshColor, ambientColor, diffuseColor;
    
    //GUI stuff
    ofParameterGroup parameters;
    ofParameter<float> a1value, a2value, n1value, n2value, n3value, n4value;
    ofParameter<float> numpoints, speed;
    ofParameter<bool> drawWire, drawPoints;
    ofParameter<ofVec3f> mPosition;
    
    ofMesh mesh;
    float n1target, n2target, n3target, n4target, a1target, a2target;
    float mPosx, mPosy, mPosz;
    float mAngle;
    float mSpeed = 0.02;
    vector<int> lastRow;
    
    Superformula();
    
    ofVec3f sf3d(float x, float y);
    void draw();
    void update();
    void moveVertices(float fftMagnitudes);
    void keyPressed(int key);
};


#endif /* Superformula_hpp */
