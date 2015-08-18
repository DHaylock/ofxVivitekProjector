//--------------------------------------------------------------
//* Name: ofxVivatekProjector.cpp
//* Author: David Haylock
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofxVivatekProjector.h"

//--------------------------------------------------------------
void ofxVivatekProjector::openConnectionToProjector(string serialName,int baud)
{
    ofSerial::setup(serialName, baud);
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
    cout << "Projector is Turning On " << POWER_ON << endl;
}
//--------------------------------------------------------------
void ofxVivatekProjector::turnProjectorOff()
{
    unsigned char command[COMMAND_LENGTH] = POWER_OFF;
    ofSerial::writeBytes(command,COMMAND_LENGTH);
    cout << "Projector is Turning Off " << POWER_OFF << endl;
}
//--------------------------------------------------------------
string ofxVivatekProjector::getProjectorStatus()
{
    unsigned char command[COMMAND_LENGTH] = SYSTEM_STATUS;
    ofSerial::writeBytes(command,COMMAND_LENGTH);
    cout << "Getting System Status " << endl;
    
    unsigned char bytesReturned[1];
    memset(bytesReturned,0,1);
    ofSerial::readBytes(bytesReturned,1);
    
    switch (bytesReturned[0]) {
        case '0':
            return "Projector is Resetting";
            break;
        case '1':
            return "Projector is On Standby";
            break;
        case '2':
            return "Projector is Operating";
            break;
        case '3':
            return "Projector is Cooling";
            break;
        default:
            break;
    }
    
}