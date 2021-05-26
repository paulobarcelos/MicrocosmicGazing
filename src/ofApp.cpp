#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetWindowShape(1920, 1080);

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
    
    settings.setup('s', "Settings");
    settings.addCallback(&ofToggleFullscreen,"Toggle_Fullscreen");
    settings.addProperty(&hideGui, "Hide GUI", false);
    settings.addProperty(&currentEffect, "Current_Effect", 0, NUM_EFFECTS - 1, 1, 0);
    
    mainOutputSyphonServer.setName("Microcosmic Dashboard");
    individualTextureSyphonServer.setName("Microcosmic Texture");
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i<NUM_CAMERAS; i++) {
        cam[i].update();
        if(cam[i].isFrameNew()){
            effect[currentEffect].setTexture(cam[i], i);
            effect[currentEffect].update();
            
        }
        
    }
    for (int i = 0; i<NUM_VIDEOS; i++) {
        video[i].update();
        if(video[i].isFrameNew()){
            effect[currentEffect].setTexture(video[i], NUM_CAMERAS + i);
            effect[currentEffect].update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    effect[currentEffect].draw(0, 0, ofGetWidth(), ofGetHeight());
    if(!hideGui){
        effect[currentEffect].drawGUI();
        settings.draw(0,0);
    }
    mainOutputSyphonServer.publishScreen();
    individualTextureSyphonServer.publishTexture(&(effect[currentEffect].getTexture()));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    settings.keyPressed(key);
}

