//
//  Superformula.cpp
//  AudioViz_FinalProject
//
//  Created by Uyen on 29/12/2017.
//
//  Adapted from Kamend's Superformula 3D https://github.com/kamend/Superformula3d

#include "Superformula.hpp"

Superformula::Superformula() {
    
    //Setup directional, ambient and diffuse lights
    //These lights make the shape look shinier and realistic
    light.setDirectional();
    light.setOrientation(ofVec3f(0,60,60));
    
    ambientColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
    light.setAmbientColor(ambientColor);
    
    diffuseColor.set(255,0,0);
    light.setDiffuseColor(diffuseColor);
    
    mesh.enableColors();
    meshColor.set(ofRandom(255),ofRandom(255),ofRandom(255)); //assign random colours to the shape
}

//--------------------------------------------------------------
void Superformula::setupGui() {
    
    //Setup GUI
    //Allows controlling 6 parameters of the shape and enable/disable wireframe and points
    parameters.setName("Superformula");
    parameters.add(a1value.set("a1value", 1,0,5));
    parameters.add(a2value.set("a2value", 1,0,5));
    parameters.add(n1value.set("n1value", 8,0,40));
    parameters.add(n2value.set("n2value", 1,0,5));
    parameters.add(n3value.set("n3value", 1,0,5));
    parameters.add(n4value.set("n4value", 1,0,5));
    parameters.add(numpoints.set("numpoints", 0.05,0.02,0.2));
    parameters.add(drawWire.set("Draw Wireframe", false));
    parameters.add(drawPoints.set("Draw Points", false));
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
    
    //Return a 3d vector with the predefined positions based on the mathematical formula
    return ofVec3f(posx, posy, posz);
}

//---------------------------------------------------------------------
void Superformula::moveVertices(float fftMagnitudes) {
    
    //Get total number of vertices of the mesh (7939)
    int numVerts = mesh.getNumVertices();
    
    for (int i=0; i < numVerts; i++) {
        ofVec3f vert = mesh.getVertex(i);

        //Move vertices in z-axis along with the audio amplitudes
        vert.z += fftMagnitudes;
        
        mesh.setVertex(i, vert); //apply the transformation to each vertex of the mesh
    
    }
}

//--------------------------------------------------------------
void Superformula::draw() {

    ofPushMatrix();
    
    //GL Flat shading modes
    glShadeModel(GL_FLAT); //Turn on GL flat shading
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION); //specifies the vertex to be used as the source of data for flat shaded varyings
    //Reference http://docs.gl/gl3/glProvokingVertex
    
    /* 3 drawing modes: shaded, points and wireframe */
    
    //Draw shaded shape (with random and lighting)
    if(!drawPoints) {
        ofDisableAlphaBlending();
        mesh.setMode(OF_PRIMITIVE_TRIANGLES); //mesh is created from many triangles
        glEnable(GL_DEPTH_TEST); //enable depth testing
        
        //Enable and disable lighting on the mesh
        ofEnableLighting();
        light.enable();
        mesh.draw();
        light.disable();
        ofDisableLighting();
    }
    //Draw points (vertices) of the mesh
    else {
        mesh.setMode(OF_PRIMITIVE_POINTS); //change ofMesh mode to points
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_PROGRAM_POINT_SIZE_ARB);
        glPointSize(1.5f); //vertex size
        mesh.clearColors();
        ofSetColor(meshColor); //vertex color
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        mesh.draw();
    }
    
    //Draw white wireframe of the mesh
    if(drawWire) {
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        mesh.clearColors();
        ofSetColor(255,255,255,100); //white
        mesh.drawWireframe();
    }
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
}

//--------------------------------------------------------------
void Superformula::update() {
    
    //remove all vertices, colours & indices prevent drawing too many meshes which slows down the program
    mesh.clear();
    
    int N_X = ceil((2.0*PI) / numpoints); // 2PI/numpoints to +/- number of points around 360 degrees in X-axis
    int N_Y = ceil(PI / numpoints); // PI/numpoints to +/- number of points around 180 degrees in Y-axis
    
    for(int x=0; x < N_X; x++) {
        for(int y=0; y < N_Y; y++) {
            mesh.addVertex(sf3d(x,y));
            mesh.addColor(meshColor);
        }
    }
    
    mesh.addVertex(sf3d(PI/numpoints, PI/numpoints));
    mesh.addColor(meshColor);
    
    lastRow.clear();
    
    /* Create the mesh which is made up of many triangles */
    
    for(int x=0 ; x < N_X; x++) {
        for(int y=0; y < N_Y-1; y++) {
            
            if(x == N_X-1) {
                int idx1 = x * N_Y +y;
                int idx2 = x * N_Y +y+1;
                int idx3 = y+1;
                int idx4 = y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
            } else {
                int idx1 = x * N_Y +y;
                int idx2 = x * N_Y +y+1;
                int idx3 = (x+1) * N_Y +y+1;
                int idx4 = (x+1) * N_Y +y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
                if(y == N_Y-2) {
                    lastRow.push_back(idx2);
                }
            }
        }
    }
    
    int lastVertex = mesh.getNumVertices()-1;
    
    for(int i=0; i<lastRow.size()-1; i++) {
        mesh.addTriangle(lastRow[i], lastRow[i+1], lastVertex);
    }
    mesh.addTriangle(lastRow[0],lastRow[lastRow.size()-1], lastVertex);
    
    ofxMeshUtils::calcNormals(mesh);

}

//--------------------------------------------------------------
void Superformula::keyPressed(int key) {
    
    //Press 'r' to randomise mesh colour and lights colour
    if(key == 'r') {
        meshColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
        ambientColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
        diffuseColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
    }
}
