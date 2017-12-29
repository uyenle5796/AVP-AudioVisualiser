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
#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofXml.h"
#include "ofxMeshUtils.h"

class Superformula {
    
public:
    
    ofMesh mesh;
    float n1target, n2target, n3target, n4target, a1target, a2target;
    float mPosx, mPosy, mPosz;
    float mAngle;
    float mSpeed = 0.02;
    
    Superformula(float posx, float posy, float posz);
    
    //Lights
    ofLight light;
    ofColor meshColor, ambientColor, diffuseColor;
    
    void setupPanel(string name);
    ofVec3f sf3d(float x, float y);
    void draw();
    void update();
    void keyPressed(int k);
    
};


#endif /* Superformula_hpp */
