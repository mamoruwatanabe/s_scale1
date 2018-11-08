#pragma once
#include "ofMain.h"
#include "ofxEasyFft.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofxEasyFft fft; // ofxEasyFftインスタンス
    ofxPanel gui; // GUI
    ofxFloatSlider saturation; // 彩度
    
    // From here writting about circle shape
    
    ofEasyCam cam;
    void animate();
    
    float radius;
    int total;
    ofMesh world;
    
    float rot;
    float animateZPos;
    bool animation;
    
    float xoff,yoff;
};
