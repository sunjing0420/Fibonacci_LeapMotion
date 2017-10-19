#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
	
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
	ofxLeapMotion leap;
	vector <ofxLeapMotionSimpleHand> simpleHands;
    
	vector <int> fingersFound;
	ofEasyCam cam;
    int stage;
    ofPoint fingerPos;
    ofVec2f finPos;
    ofVec2f line0, line1, line2, line3, line4, line5;
    
    ofVideoPlayer myPlayer1, myPlayer2, myPlayer3, myPlayer4, myPlayer5, myPlayer6;
    
    ofSoundPlayer   mySound;
  
    
};
