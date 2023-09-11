#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    // Set Scale of grid
    scl = 6;
    
    // terrainZPos = 84;
    exponent = 3;
    minTerrainZPos = 16;
    maxTerrainZPos = 48;
    terrainW = 1024;
    terrainH = 1024;
    
    cols = terrainW / scl;
    rows = terrainH / scl;
    
    // Initialize the mesh
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            float x = i * scl;
            float y = j * scl;
            float z = 0; // Initialize z to 0
            mesh.addVertex(ofVec3f(x, y, z));
            mesh.addColor(ofFloatColor(1, 1, 1));
        }
    }
    
    // Create indices for the triangles
    for (int j = 0; j < rows - 1 ; j++) {
        for (int i = 0 ; i < cols - 1; i++) {
            mesh.addIndex(i + j * cols);
            mesh.addIndex((i + 1) + j * cols);
            mesh.addIndex(i + (j + 1) * cols);
            
            mesh.addIndex((i + 1) + j * cols);
            mesh.addIndex((i + 1) + (j + 1) * cols);
            mesh.addIndex(i + (j + 1) * cols);
        }
    }
    
    // Update the mesh based on Perlin noise
    for (int j = 0; j < rows; j++) {
        float t = float(rows - j) / rows;
        t = pow(t, exponent);
        float terrainZPos = t * (maxTerrainZPos - minTerrainZPos) + minTerrainZPos;
        
        for (int i = 0; i < cols; i++) {
            float z = ofMap(ofNoise(i * 0.1, j * 0.1), 0, 1, -terrainZPos, terrainZPos);
            mesh.setVertex(i + j * cols, ofVec3f(i * scl, j * scl, z));
        }
    }
    
    light.setDiffuseColor(ofFloatColor(.85, .85, .55));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

    // MARK: Export
    
    vector<ofPrimitiveMode> modes = {
        OF_PRIMITIVE_TRIANGLES,
        OF_PRIMITIVE_LINES,
        OF_PRIMITIVE_POINTS,
    };
    
    for(auto mode : modes) {
        // Set the mode for the mesh
        mesh.setMode(mode);
        
        // Setup FBO (Frame Buffer Object)
        ofFbo fbo;
        fbo.allocate(terrainW, terrainH, GL_RGBA);
        fbo.begin();
        
        ofClear(255,255,255, 0);
        
        // Translate and rotate to draw the mesh
        ofTranslate(fbo.getWidth()/2, fbo.getHeight()/2);
        ofRotateX(75);
        ofTranslate(-terrainW / 2, -terrainH / 2);
        
        mesh.drawWireframe();
        
        fbo.end();
        
        // Read from FBO and save to file
        ofPixels pixels;
        fbo.readToPixels(pixels);
        
        string filename = "terrain_" + to_string(mode) + ".png";
        ofSaveImage(pixels, filename);
    }
    std::cout << "Images Exported" << std::endl;
    
    // Optionally close the application
    // ofExit();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    // mesh.setMode(OF_PRIMITIVE_LINES);
    // mesh.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------

void ofApp::update(){
    float time = ofGetElapsedTimef();
    
    // Create a smoothly varying value for z-coordinate
    for (int j = 0; j < rows; j++) {
        // Calculate dynamic terrainZPos based on row index and using power function
        float t = float(rows - j) / rows; // Normalize j to [0, 1] and invert it
        t = pow(t, exponent);
        float terrainZPos = t * (maxTerrainZPos - minTerrainZPos) + minTerrainZPos;
        
        for (int i = 0; i < cols; i++) {
            float z = ofMap(ofNoise(i * 0.05, j * 0.05, time * 0.5), 0, 1, -terrainZPos, terrainZPos);
            mesh.setVertex(i + j * cols, ofVec3f(mesh.getVertex(i + j * cols).x, mesh.getVertex(i + j * cols).y, z));
        }
    }
    
    light.setPosition(ofVec3f(0, sin(time) * 100, 0));
}

//--------------------------------------------------------------

void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5 - terrainW * 0.5 + scl * 0.5, ofGetHeight() * 0.5 - terrainH * 0 + scl * 0.5);
    ofRotateX(70);
    ofTranslate(0, terrainH * 0.2);
    
    ofEnableLighting();
    light.enable();
    
    mesh.draw();
    
    light.disable();
    ofDisableLighting();
    
    ofSetColor(255);
    mesh.drawWireframe();
    
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
