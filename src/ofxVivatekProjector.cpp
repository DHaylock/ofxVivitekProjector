//--------------------------------------------------------------
//* Name: ofxVivatekProjector.cpp
//* Author: David Haylock, Stewart Morgan
//* Creation Date: 17-08-2015
//--------------------------------------------------------------
#include "ofxVivatekProjector.h"

//--------------------------------------------------------------
void ofxVivatekProjector::openConnectionToProjector(string serialName,int baud)
{
    currentSerialName = serialName;
    currentBaud = baud;
    projectorPort.listDevices();
    projectorPort.setup(serialName, baud);
}
//--------------------------------------------------------------
void ofxVivatekProjector::close()
{
    projectorPort.flush();
    projectorPort.drain();
    projectorPort.close();
}
//--------------------------------------------------------------
void ofxVivatekProjector::reconnect() {
    if(projectorPort.isInitialized()) {
        cout << "Reconnecting to projector..." << endl;
        projectorPort.close();
        projectorPort.setup(currentSerialName, currentBaud);
    }
}
//--------------------------------------------------------------
bool ofxVivatekProjector::isConnected()
{
    return projectorPort.isInitialized();
}
//--------------------------------------------------------------
bool ofxVivatekProjector::doCommand(const char *command, unsigned int command_length, unsigned char *reply, unsigned int reply_size)
{
    bool            free_reply = false;
    bool            return_value = false;
    unsigned int    reply_length = 0;
    unsigned int    timeout = TIMEOUT_DURATION;

    if(reply == NULL && reply_size == 0) {
        free_reply = true;
        reply_size = 1024;
        reply = (unsigned char*)malloc(reply_size);
    
    } else if(reply_size == 0) {
        cout << "Projector reply buffer size cannot be zero!" << endl;
        return false;

    } else {
        free_reply = false;
        memset(reply, 0, reply_size);
    }
        
    // Drop off the trailing NULL
    command_length--;
    
    cout << "Sending " << command_length << " bytes to the projector: " << command << endl;
    projectorPort.writeBytes((unsigned char *)command, command_length);

    // Give the projector a quarter of a second to reply
    usleep(TIMEOUT_STEP_DURATION);
    
    while(timeout != 0) {
        switch(int byte = projectorPort.readByte()) {
        
            case OF_SERIAL_NO_DATA:
                cout << "Projector has no data; waiting (" << timeout << " retries remaining)..." << endl;
                timeout--;
                usleep(TIMEOUT_STEP_DURATION);
                continue;

            case OF_SERIAL_ERROR:
                cout << "Projector returned error" << endl;
                return false;

            case '\r':
                cout << "Projector replied: " << reply << endl;
                projectorPort.drain();
                return_value = (reply_length > 0) && (reply[0] == 'P');
                if(free_reply) {
                    free(reply);
                }
                return return_value;

            default:
                if(reply_length == reply_size) {
                    cout << "Read too much from the projector for the buffer!!" << endl;
                    return false;
                }

                //cout << "Projector sent: " << byte << " AKA " << (unsigned char)byte << endl;
                reply[ reply_length++ ] = (unsigned char)byte;
                break;
        }
    }

    cout << "Timed-out waiting for data from the projector!" << endl;
    if(free_reply) {
        free(reply);
    }
    return false;
}
//--------------------------------------------------------------
bool ofxVivatekProjector::setProjectionMode(int mode)
{
    switch(mode) {
        case 0:
            cout << "Projecting in Front Mode..." << endl;
            return doCommand(COMMAND_MODE_FRONT, sizeof(COMMAND_MODE_FRONT));

        case 1:
            cout << "Projecting in Rear Mode..." << endl;
            return doCommand(COMMAND_MODE_REAR, sizeof(COMMAND_MODE_REAR));

        case 2:
            cout << "Projecting in Ceiling Mode..." << endl;
            return doCommand(COMMAND_MODE_FRONT_CEILING, sizeof(COMMAND_MODE_FRONT_CEILING));
            
        case 3:
            cout << "Projecting in Rear/Ceiling Mode..." << endl;
            return doCommand(COMMAND_MODE_REAR_CEILING, sizeof(COMMAND_MODE_REAR_CEILING));
            
        default:
            cout << "Unknown mode to project in!" << endl;
            return false;
    }
}
//--------------------------------------------------------------
bool ofxVivatekProjector::resetProjector()
{
    cout << "Projector is resetting..." << endl;
    return doCommand(COMMAND_SYSTEM_RESET, sizeof(COMMAND_SYSTEM_RESET));
}

//--------------------------------------------------------------
bool ofxVivatekProjector::resyncProjector()
{
    cout << "Projector is resyncing..." << endl;
    return doCommand(COMMAND_RESYNC, sizeof(COMMAND_RESYNC));
}

//--------------------------------------------------------------
bool ofxVivatekProjector::turnProjectorOn()
{
    cout << "Projector is Turning On..." << endl;
    return doCommand(COMMAND_POWER_ON, sizeof(COMMAND_POWER_ON));
}
//--------------------------------------------------------------
bool ofxVivatekProjector::turnProjectorOff()
{
    cout << "Projector is Turning Off..." << endl;
    return doCommand(COMMAND_POWER_OFF, sizeof(COMMAND_POWER_OFF));
}
//--------------------------------------------------------------
string ofxVivatekProjector::getProjectorStatus()
{
    cout << "Getting System Status..." << endl;
    unsigned char reply[1024];
    if(doCommand(COMMAND_SYSTEM_STATUS, sizeof(COMMAND_SYSTEM_STATUS), reply, sizeof(reply))) {
        return ofToString(reply);
    }
    return "";
}
//--------------------------------------------------------------
int ofxVivatekProjector::getLampHours()
{
    cout << "Getting lmap-hours..." << endl;
    unsigned char reply[1024];
    if(doCommand(COMMAND_GET_LAMP_HOURS, sizeof(COMMAND_GET_LAMP_HOURS), reply, sizeof(reply))) {
        return (int)std::strtol((const char *)(reply + 1), (char **)NULL, 10);
    }
    return -1;
}