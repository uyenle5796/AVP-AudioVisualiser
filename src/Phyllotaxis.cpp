//
//  Phyllotaxis.cpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 29/12/2017.
//

#include "Phyllotaxis.hpp"

//--------------------------------------------------------------
Phyllotaxis::Phyllotaxis() {
    //empty
 }

//--------------------------------------------------------------
void Phyllotaxis::setupGui() {
    
    //Setup GUI
    parameters.setName("Phyllotaxis");
    parameters.add(angleDeg.set("Angle degree", 137.3, 137.0, 140.0));
    parameters.add(rotateDeg.set("Rotation degree", 0.3, 0.2, 0.5));
    parameters.add(scaling.set("Scaling", 8, 1, 10));
    parameters.add(color.set("Colours", 255, 1, 350));
}


//--------------------------------------------------------------
void Phyllotaxis::draw(float fftMagnitudes) {

    ofPushMatrix();
    ofRotate(n * rotateDeg); //rotate the shape according to number of florets and a degree value
    
    //Draw the Phyllotaxis spiral shape using a for loop, where 'n' increments by 5 every frame (in update). This makes the shape grow bigger.
    for (int i = 0; i < n; i++) {
        
        //Create the Phyllotaxis pattern based on the mathematical formula: http://algorithmicbotany.org/papers/abop/abop-ch4.pdf
        angle = i * angleDeg;
        r = scaling * sqrt(i);
        float x = r * cos(angle);
        float y = r * sin(angle);
        
        //Set rainbow colours
        float hue = i + startColor;
        hue = i % int(color);
        ofColor col;
        col.setHsb(hue, 255, 255);
        ofSetColor(col);
        
        //Assign amplitudes of the audio sample using FFT and assign it to z values of each floret
        //so that the floret moves in z axis along with the audio amplitudes
        float z = fftMagnitudes * 20; //scale up the magnitudes 20 times to make the effect easier to see
        
        ofDrawEllipse(x, y, z, 3, 3); //Draw lots of ellipses of size 3 using predefined positions
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void Phyllotaxis::update() {
    
    //Make the shape grow bigger by adding one floret every frame.
    //However this slows the program down significantly when 'n' gets too large. So I added a limit so the shape stops growing at 500 florets to maintain performance.
    if (n <= 500)
        n ++;
    
    //Increment colours to create rainbow effect
    startColor += scaling;
}
