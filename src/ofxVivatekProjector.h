//--------------------------------------------------------------
//* Name: ofxVivatekProjector.h
//* Author: David Haylock
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofMain.h"


#define POWER_ON "VXXS0001\r"
#define POWER_OFF "VXXS0002\r"
#define SYSTEM_STATUS "VXXS0007\r"

#define COMMAND_LENGTH 10
#define BAUD 9600

class ofxVivatekProjector : public ofSerial {
    public:
        void openConnectionToProjector(string serialName,int baud = BAUD);
        void close();
    
        bool isConnected();
    
        void turnProjectorOn();
        void turnProjectorOff();
        string getProjectorStatus();
    
    protected:
    
    
    private:
};