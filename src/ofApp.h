#pragma once

#define NUM_CAMERAS 3
#define NUM_VIDEOS 2
#define NUM_EFFECTS 5

#include "ofMain.h"
#include "ofxPatches.h"
#include "ofxKeyboardSettings.h"


class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);

        ofVideoGrabber cam[NUM_CAMERAS];
        ofVideoPlayer video[NUM_VIDEOS];
        ofxPatches::Manager effect[NUM_EFFECTS];
        ofxKeyboardSettings settings;
        int currentEffect;
};
