#include "ofApp.h"


void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    
    // From here I will write the Circle code
    
    radius = 50;
    total = 3;
    rot = 0;
    animateZPos = 1;
    
    world.setMode(OF_PRIMITIVE_TRIANGLES);
    
    animation = true;
    for (int i=0; i < total; i++){
        float lat = ofMap(i, 0, total-1, 0, 0, PI);
        
        for (int j=0; j<total; j++){
            float lon = ofMap(j, 0, total-1, 0, 0, TWO_PI);
        
        float x = radius * sin(lat) * cos(lon);
        float y = radius * sin(lat) * sin(lon);
        float z = radius * cos(lat);
        
        world.addVertex(ofVec3f(x,y,z));
        }
    }
    
    for (int j=0; j < total -1; j ++){
        for(int i=0; i < total -1; i++){
            
            world.addIndex(i+j*total);         // 0
            world.addIndex((i+1)+j*total);     // 1
            world.addIndex(i+(j+1)*total);     // 6
            
            world.addIndex((i+1)+j*total);     // 1
            world.addIndex((i+1)+(j+1)*total); // 7
            world.addIndex(i+(j+1)*total);     // 6
        }
    }
    
    // TEST FFT
    fft.setup(pow(2.0, 10.0));

}
    


void ofApp::update(){
   fft.update(); // FFT更新
    
    animate();
}

void ofApp::draw(){
    
    
    // From here I start to Write Circle code
    
    ofBackgroundGradient(ofColor(40, 40, 40), ofColor(50, 50, 50), OF_GRADIENT_CIRCULAR);
    
    cam.begin();
    
    ofPushMatrix();
    ofRotateX(rot);
    ofRotateY(rot);
    ofSetColor(255, 255, 255);
    world.drawWireframe();
    
    for (int i=0; i < world.getVertices().size(); i++) {
        
        float x = world.getVertex(i).x;
        float y = world.getVertex(i).y;
        float z = world.getVertex(i).z;
        
        ofSetColor(255, 0, 0);
        
       // float sanim = 1.1;
      //  ofDrawSphere(x*sanim, y*sanim, z*sanim, 1);
        
        
    }
    
    ofPopMatrix();
    
    cam.end();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 30);
    
    vector<float> buffer;
    buffer = fft.getBins();
    
    ofSetLineWidth(ofGetWidth() / float(buffer.size()) / 2.0);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    
    ////
    
    for (int i = 0; i < buffer.size(); i++) {
        // 色を設定
        float hue = ofMap(i, 0, buffer.size(), 0, 160);
        float br = ofMap(buffer[i], 0, 1, 0, 255);
        ofColor col;
        col.setHsb(hue, saturation, br);
        ofSetColor(col);
        // 右
        float rx = ofMap(i, 0, buffer.size(), 0, ofGetWidth() / 2.0);
        ofCircle(100, -100, 100, 100);
        ofSetCircleResolution(50);
        
        ofCircle(100, 400, 100, 100);
        ofSetCircleResolution(50);


        // 左
        float lx = ofMap(i, 0, buffer.size(), 0, -ofGetWidth() / 2.0);
        ofLine(lx, -ofGetWidth() / 2.0, lx, ofGetWidth() / 2.0);
    }
    
}



    
    // End the Coding of Circle
    
    /*
    // float型の配列にFFT結果を格納
    vector<float> buffer;
    buffer = fft.getBins();
    // グラフに描画
    ofSetLineWidth(ofGetWidth() / float(buffer.size()) / 2.0);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < buffer.size(); i++) {
        // 色を設定
        float hue = ofMap(i, 0, buffer.size(), 0, 160);
        float br = ofMap(buffer[i], 0, 1, 0, 255);
        ofColor col;
        col.setHsb(hue, saturation, br);
        ofSetColor(col);
        // 右
        float rx = ofMap(i, 0, buffer.size(), 0, ofGetWidth() / 2.0);
        ofLine(rx, -ofGetWidth() / 2.0, rx, ofGetWidth() / 2.0);
        // 左
        float lx = ofMap(i, 0, buffer.size(), 0, -ofGetWidth() / 2.0);
        ofLine(lx, -ofGetWidth() / 2.0, lx, ofGetWidth() / 2.0);
    }
    ofPopMatrix();
    gui.draw(); // GUI描画
}
*/

    void ofApp::animate() {
    
    world.clear();
    for (int i= 0; i < total; i++) {
        float lat = ofMap(i,0,total-1,0.0,PI);
        
        for (int j= 0; j<total; j++) {
            float lon = ofMap(j,0,total-1,0.0,TWO_PI);
            
            if(animation)
                animateZPos = ofMap(ofNoise(i*ofGetElapsedTimef()*0.05, j*ofGetElapsedTimef()*0.05),0,1,-10,10);
            
            
            float x = (animateZPos+radius) * sin(lat) * cos(lon);
            float y = (animateZPos+radius) * sin(lat) * sin(lon);
            float z = (animateZPos+radius) * cos(lat);
            
            world.addVertex(ofVec3f(x,y,z));
            
            
            
            
            //ofSetColor(255, 0, 0);
            
        }
        
    }
    
    for (int j = 0; j < total - 1; j++) {
        for (int i = 0 ; i < total - 1 ; i++) {
            
            world.addIndex(i+j*total);         // 0
            world.addIndex((i+1)+j*total);     // 1
            world.addIndex(i+(j+1)*total);     // 6
            
            world.addIndex((i+1)+j*total);     // 1
            world.addIndex((i+1)+(j+1)*total); // 7
            world.addIndex(i+(j+1)*total);     // 6
        }
    }
    
    if(animation) {
        rot = rot + 0.3;
    }
    }
