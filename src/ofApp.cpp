#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofLog() << "GL Version" << glGetString( GL_VERSION );
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableAntiAliasing();
    
    int camWidth 		= 640;	// try to grab at this size.
    int camHeight 		= 480;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);

    
    //shader.setGeometryInputType(GL_TRIANGLE_STRIP);
    //shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    //shader.setGeometryOutputCount(4);
    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");
    
    //shader.load("shaders/vert.glsl", "shaders/frag.glsl");
    
    texturePatternImg.load("yellowstripes.png");
    
    fbo.allocate(ofGetWidth(),ofGetHeight());
    
    // Let's clear the FBOs
    // otherwise it will bring some junk with it from the memory
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    sphere.setRadius(300);
    sphere.setResolution(25);
    sphere.mapTexCoords(0, 0, vidGrabber.getWidth(), vidGrabber.getHeight());
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    //movie.update()

    fbo.begin();
    ofClear(0, 0, 0,255);
    
    //texturePatternImg.getTexture().bind();
    
    shader.begin();
    
    
    
    ofSetColor(0, 255, 255, 126);
    
    // translate plane into center screen.
    float tx = ofGetWidth() / 2;
    float ty = ofGetHeight() / 2;
    ofTranslate(tx, ty);
    
    //sphere.drawWireframe();
    sphere.draw();
    //texturePatternImg.draw(0, 0);
    
    
    
    // set thickness of ribbons
    shader.setUniform1f("thickness", 10);
    
    // make light direction slowly rotate
    shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/20), cos(ofGetElapsedTimef()/20), 0);
    
    shader.setUniform2f("resolution", ofVec2f(vidGrabber.getWidth(), vidGrabber.getHeight()));
    shader.setUniform2f("mouse", ofVec2f(mouseX, mouseY));
    shader.setUniform1f("time", ofGetElapsedTimef());
    
    // Pass the video texture
    //shader.setUniformTexture("tex0", texturePatternImg.getTexture() , 1 );
    shader.setUniformTexture("tex0", vidGrabber.getTexture(), 1);
    
    shader.end();
    
    //texturePatternImg.getTexture().unbind();
    
    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.draw(0, 0);
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
