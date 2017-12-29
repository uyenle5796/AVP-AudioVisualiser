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
void Superformula::setup() {

    parameters.add(a1value.set("a1value", 1,0,5)); //name, value, min, max
    parameters.add(a2value.set("a2value", 1,0,5));
    parameters.add(n1value.set("n1value", 8,0,40));
    parameters.add(n2value.set("n2value", 1,0,5));
    parameters.add(n3value.set("n3value", 1,0,5));
    parameters.add(n4value.set("n4value", 1,0,5));
    parameters.add(numpoints.set("Number of Points", 0.05,0.02,0.9));
    parameters.add(speed.set("Speed", 10, 0, 20));
    parameters.add(drawWire.set("Draw Wireframe", true));
    parameters.add(drawPoints.set("Draw Points", true));
}

//--------------------------------------------------------------
ofVec3f Superformula::sf3d(float x, float y) {

    //Create the Superformula shape based on the mathematical formula: https://en.wikipedia.org/wiki/Superformula
    
    // Latitude and Longitude angles
    float i = -PI + x*numpoints; //Longitude varies from -PI to PI
    float j = -PI/2.0 + y*numpoints; //Latitude varies from -PI/2 to PI/2
    
    // First Superformula (r1)
    float raux1 = pow(abs(1/a1value*abs(cos(n1value * i/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*i/4))),n4value);
    float r1 = pow(abs(raux1),(-1/n2value));
    
    // Second Superformula (r2)
    float raux2 = pow(abs(1/a1value*abs(cos(n1value*j/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*j/4))),n4value);
    float r2 = pow(abs(raux2),(-1/n2value));
    
    float posx = r1*cos(i)*r2*cos(j)*100.0f;
    float posy = r1*sin(i)*r2*cos(j)*100.0f;
    float posz = r2*sin(j)*100.0f;
    
    return ofVec3f(posx, posy, posz);
}

//--------------------------------------------------------------
void Superformula::draw() {

    ofPushMatrix();
    ofTranslate(mPosx-300, mPosy, mPosz);
    
    glShadeModel(GL_FLAT);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
    
    if(!drawPoints) {
        ofDisableAlphaBlending();
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        glEnable(GL_DEPTH_TEST);
        ofEnableLighting();light.enable();
        mesh.draw();
        light.disable();ofDisableLighting();
    } else {
        mesh.setMode(OF_PRIMITIVE_POINTS);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_PROGRAM_POINT_SIZE_ARB);
        glPointSize(0.5f);
        mesh.clearColors();
        ofSetColor(255,255,255,100);
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        mesh.draw();
    }
    
    if(drawWire) {
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        mesh.clearColors();
        ofSetColor(255,255,255,100);
        mesh.drawWireframe();
    }
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
}

//--------------------------------------------------------------
void Superformula::update() {
    
    mesh.clear();
    int N_X = ceil((2.0*PI) / numpoints);
    int N_Y = ceil(PI / numpoints);
    
    for(int x=0;x<N_X;x++) {
        for(int y=0;y<N_Y;y++) {
            mesh.addVertex(sf3d(x,y));
            mesh.addColor(ofColor(255,255,255,100));
        }
    }
    
    mesh.addVertex(sf3d(PI/numpoints,PI/numpoints));
    mesh.addColor(ofColor(255,30,30));
    
    lastRow.clear();
    
    for(int x=0;x<N_X;x++) {
        for(int y=0;y<N_Y-1;y++) {
            
            if(x == N_X-1) {
                
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = y+1;
                int idx4 = y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
            } else {
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = (x+1)*N_Y+y+1;
                int idx4 = (x+1)*N_Y+y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
                if(y == N_Y-2) {
                    lastRow.push_back(idx2);
                }
            }
        }
    }
    
    int lastVertex = mesh.getNumVertices()-1;
    
    for(int i=0;i<lastRow.size()-1;i++) {
        mesh.addTriangle(lastRow[i], lastRow[i+1], lastVertex);
    }
    mesh.addTriangle(lastRow[0],lastRow[lastRow.size()-1], lastVertex);
    
    ofxMeshUtils::calcNormals(mesh);
}

//--------------------------------------------------------------
void Superformula::keyPressed(int key) {
    
}
