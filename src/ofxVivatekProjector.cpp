//--------------------------------------------------------------
//* Name: ofxVivatekProjector.cpp
//* Author: David Haylock
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofxVivatekProjector.h"

//--------------------------------------------------------------
void ofxVivatekProjector::openConnection(string port, int baud)
{
    ofSerial::setup(port, baud);
    ofSerial::listDevices();
}
//--------------------------------------------------------------
void ofxVivatekProjector::close()
{
    ofSerial::close();
}
//--------------------------------------------------------------
bool ofxVivatekProjector::isConnected()
{
    return ofSerial::isInitialized();
}
//--------------------------------------------------------------
void ofxVivatekProjector::turnProjectorOn()
{
    unsigned char command[COMMAND_LENGTH] = POWER_ON;
    ofSerial::writeBytes(command,COMMAND_LENGTH);
    cout << "Projector is Turning On" << POWER_ON << endl;
}
//--------------------------------------------------------------
void ofxVivatekProjector::turnProjectorOff()
{
    unsigned char command[COMMAND_LENGTH] = POWER_OFF;
    ofSerial::writeBytes(command,COMMAND_LENGTH);
    cout << "Projector is Turning Off" << POWER_OFF << endl;
}