#pragma once

#include "ofMain.h"
#include "ofxVivitekProjector.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
    
        ofxVivitekProjector projector;
        ofTrueTypeFont title;
};
