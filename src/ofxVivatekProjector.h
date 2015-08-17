//--------------------------------------------------------------
//* Name: ofxVivatekProjector.h
//* Author: David Haylock
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofMain.h"


#define POWER_ON "* 0 IR 001\r"
#define POWER_OFF "* 0 IR 002\r"
#define COMMAND_LENGTH 13
#define BAUD 4800

class ofxVivatekProjector : public ofSerial {
    public:
        void openConnectionToProjector(string serialName,int baud = BAUD);
        void close();
    
        bool isConnected();
    
        void turnProjectorOn();
        void turnProjectorOff();
    
    protected:
    
    
    private:
};