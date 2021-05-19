#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFullscreen(true);

    for (int i = 0; i<NUM_CAMERAS; i++) {
        cam[i].setDeviceID(i);
        cam[i].initGrabber(1280, 720);
    }
    
    for (int i = 0; i<NUM_VIDEOS; i++) {
        video[i].load("videos/" + ofToString(i) + ".mov");
        video[i].setLoopState(OF_LOOP_NORMAL);
        video[i].setVolume(0);
        video[i].play();
    }
    
    for (int i = 0; i<NUM_EFFECTS; i++) {
        effect[i].setup(NUM_CAMERAS + NUM_VIDEOS, "effect" + ofToString(i));
        effect[i].allocate(1280, 720);
        OFX_PATCHES_REGISTER_ALL_EFFECTS(effect[i]);
        effect[i].loadSettings();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i<NUM_CAMERAS; i++) {
        cam[i].update();
        if(cam[i].isFrameNew()){
            for (int j = 0; j<NUM_EFFECTS; j++) {
                effect[j].setTexture(cam[i], i);
                effect[j].update();
            }
            
        }
        
    }
    for (int i = 0; i<NUM_VIDEOS; i++) {
        video[i].update();
        if(video[i].isFrameNew()){
            for (int j = 0; j<NUM_EFFECTS; j++) {
                effect[j].setTexture(video[i], NUM_CAMERAS + i);
                effect[j].update();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int j = 0; j<NUM_EFFECTS; j++) {
        effect[j].drawGUI();
    }
}

