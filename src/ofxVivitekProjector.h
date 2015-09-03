//--------------------------------------------------------------
//* Name: ofxVivitekProjector.h
//* Author: David Haylock, Stewart Morgan
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofMain.h"
#include <stdlib.h>

#define TIMEOUT_STEP_DURATION      250000   // In uSeconds
#define TIMEOUT_DURATION           20       // In iterations of TIMEOUT_STEP_DURATION, 20 ~5s

#define COMMAND_POWER_ON            "V99S0001\r"
#define COMMAND_POWER_OFF           "V99S0002\r"
#define COMMAND_RESYNC              "V99S0003\r"
#define COMMAND_GET_LAMP_HOURS      "V99G0004\r"
#define COMMAND_SYSTEM_RESET        "V99S0006\r"
#define COMMAND_SYSTEM_STATUS       "V99G0007\r"

#define COMMAND_MODE_FRONT          "V99S03080\r"
#define COMMAND_MODE_REAR           "V99S03081\r"
#define COMMAND_MODE_FRONT_CEILING  "V99S03082\r"
#define COMMAND_MODE_REAR_CEILING   "V99S03083\r"

#define COMMAND_SET_ASPECT_FILL     "V99S03010\r"
#define COMMAND_SET_ASPECT_4_3      "V99S03011\r"
#define COMMAND_SET_ASPECT_16_9     "V99S03012\r"
#define COMMAND_SET_ASPECT_LETTERBOX "V99S03013\r"
#define COMMAND_SET_ASPECT_NATIVE   "V99S03014\r"

//#define COMMAND_SET_VERTICAL_KEYSTONE "V99G0309\r"

#define NUM_BYTES 1

#define BAUD 9600

class ofxVivitekProjector {
    public:
        void openConnectionToProjector(string serialName,int baud = BAUD);
        void close();
    
        bool isConnected();
        void reconnect();
        bool doCommand(const char *command, unsigned int command_length, unsigned char *reply = NULL, unsigned int reply_size = 0);
    
        bool resyncProjector();
        bool resetProjector();
        bool turnProjectorOn();
        bool turnProjectorOff();
        bool setProjectionMode(int mode);
        bool setProjectionAspect(int mode);
    
        string getProjectorStatus();
        int getLampHours();
    
    protected:
        unsigned char returnValue;
        ofSerial projectorPort;
        unsigned char	bytesReturned[NUM_BYTES];
        string  messageBuffer;
        string message;
    
    private:
        string currentSerialName;
        int currentBaud;
};