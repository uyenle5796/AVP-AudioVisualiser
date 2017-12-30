//
//  Phyllotaxis.cpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 29/12/2017.
//

#include "Phyllotaxis.hpp"

//--------------------------------------------------------------
Phyllotaxis::Phyllotaxis() {
    
 }

//--------------------------------------------------------------
void Phyllotaxis::setupGui() {
    
    parameters.setName("Phyllotaxis");
    parameters.add(angleDeg.set("Angle degree", 137.3, 137.0, 140.0));
    parameters.add(rotateDeg.set("Rotation degree", 0.3, 0.2, 0.5));
    parameters.add(scaling.set("Scaling", 8, 1, 10));
    parameters.add(colorVal.set("Colours", 300, 1, 360));
}


//--------------------------------------------------------------
void Phyllotaxis::draw(float magnitudes) {

    ofPushMatrix();
    ofRotate(n * rotateDeg);
    
    //Draw the Phyllotaxis spiral shape using a for loop, where 'n' increments by 5 every frame (in update). This makes the shape grow bigger.
    for (int i = 0; i < n; i++) {
        
        //Create the Phyllotaxis pattern based on the mathematical formula: http://algorithmicbotany.org/papers/abop/abop-ch4.pdf
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
//        for(int j=0; j < bufferSize; j++) {
//            float z = magnitudes * intensity; //scale up the magnitudes by multiplying with a value to make the effect easier to see
//        }
        float z = magnitudes * 20; //scale up the magnitudes 20 times to make the effect easier to see
        ofDrawEllipse(x, y, z, 3, 3);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void Phyllotaxis::update() {
    
    //Make the shape grow by adding one floret every frame.
    //However this makes the the program slows down significant when 'n' gets too large. So I added a limit so the shape stops growing at 500 florets to maintain performance.
    if (n <= 500)
        n ++;
    
    //Increment colours to create rainbow effect
    start += scaling;
}
