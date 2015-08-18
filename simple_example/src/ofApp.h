#pragma once

#include "ofMain.h"
#include "ofxVivatekProjector.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
    
        ofxVivatekProjector projector;
        ofTrueTypeFont title;
};
