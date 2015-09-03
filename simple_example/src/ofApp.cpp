//--------------------------------------------------------------
//* Name: ofApp.cpp
//* Author: David Haylock, Stewart Morgan
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0, 0, 0);
    title.loadFont("mono.ttf",15,true,false,false,0.3,75);
    projector.openConnectionToProjector("/dev/tty.usbserial");
}
//--------------------------------------------------------------
void ofApp::update()
{

}
//--------------------------------------------------------------
void ofApp::draw()
{
    title.drawString("ofxVivitekProjector: Simple", 10, 20);
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
//    projector.turnProjectorOff();
    projector.close();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    string status;
    int lamp_hours;
    
    switch (key) {
        case '0':
            projector.setProjectionMode(0);
            break;
        case '1':
            projector.setProjectionMode(1);
            break;
        case '2':
            projector.setProjectionMode(2);
            break;
        case '3':
            projector.setProjectionMode(3);
            break;

        case 'c':
            projector.turnProjectorOff();
            break;
            
        case 'g':
            status = projector.getProjectorStatus();
            if(status == "") {
                cout << "Failed to get projector status" << endl;
            } else {
                cout << "Projector status is currently: " << status << endl;
            }
            break;
            
        case 'l':
            lamp_hours = projector.getLampHours();
            if(lamp_hours < 0) {
                cout << "Failed to get projector lamp-hours" << endl;
            } else {
                cout << "Projector lamp-hours is currently: " << lamp_hours << endl;
            }
            break;
            
        case 'o':
            projector.turnProjectorOn();
            break;
            
        case 'r':
            projector.resetProjector();
            break;
            
        case 'R':
            projector.reconnect();
            break;

        case 's':
            projector.resyncProjector();
            break;
            
        case 'h':
            cout << "Help:" << endl;
            cout << "c: Turn Off" << endl;
            cout << "g: Get Current status" << endl;
            cout << "l: Get Lamp hours" << endl;
            cout << "o: Turn On " << endl;
            cout << "r: Reset Projector" << endl;
            cout << "R: Reconnect serial link" << endl;
            cout << "s: Resync Projector" << endl;
            cout << "h: This help screen" << endl;
            break;

        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}