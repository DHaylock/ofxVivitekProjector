#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0, 0, 0);
    title.loadFont("mono.ttf",15,true,false,false,0.3,75);
    projector.openConnectionToProjector("thisport");
}
//--------------------------------------------------------------
void ofApp::update()
{

}
//--------------------------------------------------------------
void ofApp::draw()
{
    title.drawString("ofxVivatekProjector: Simple", 10, 20);
    if (projector.isConnected()) {
        ofDrawBitmapString("Projector is Connected", 10,50);
    }
    else {
        ofDrawBitmapString("Projector is Not Connected", 10,50);
    }
}
//--------------------------------------------------------------
void ofApp::exit()
{
    projector.turnProjectorOff();
    projector.close();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'o') {
        projector.turnProjectorOn();
    }
    if (key == 'c') {
        projector.turnProjectorOff();
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}