//
//  Phyllotaxis.hpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 29/12/2017.
//

#ifndef Phyllotaxis_hpp
#define Phyllotaxis_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"

class Phyllotaxis {

public:
    
    //Gui stuff
    ofParameterGroup parameters;
    ofParameter<float> angleDeg, rotateDeg, scaling, colorVal;
    
    float angle; //Divergence angle
    float r; //distance between the center of the capitulum and the center of the nth floret
    float n; //ordering number of the a floret, counting outward from the center
    float start = 0;
    
    void setupGui();
    void draw(float magnitudes);
    void update();

    Phyllotaxis();
    
};

#endif /* Phyllotaxis_hpp */
