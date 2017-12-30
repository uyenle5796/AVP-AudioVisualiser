//
//  Ring.hpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 30/12/2017.
//

#ifndef Ring_hpp
#define Ring_hpp

#include <stdio.h>

#include "ofMain.h"
#include "ofxGui.h"

class Ring {
    
public:
    
    Ring();
    
    ofParameterGroup parameters;
    ofParameter<float>  radius, spacing, color, intensity, scale;
    
    vector<float> particles;
//    float scale = 10;
    float startColor; //a start value for creating rainbow color
    
    void setupGui();
    void draw(float fftMagnitudes);
    void update();
};

#endif /* Ring_hpp */
