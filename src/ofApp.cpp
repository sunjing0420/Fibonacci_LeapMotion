#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
	leap.open();
    
	cam.setOrientation(ofPoint(-20, 0, 0));
    
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    stage = 0;
    
    line0 = ofVec2f(10, -90);
    line1 = ofVec2f(0, -89);
    line2 = ofVec2f(0, -107);
    line3 = ofVec2f(24, -107);
    line4 = ofVec2f(28, -70);
    line5 = ofVec2f(-50, -70);
    
    myPlayer1.load("videos/p123.mp4");
    myPlayer2.load("videos/p4.mp4");
    myPlayer3.load("videos/p5.mp4");
    myPlayer4.load("videos/p6.mp4");
    myPlayer5.load("videos/p7.mp4");
    myPlayer6.load("videos/p8.mp4");
    myPlayer1.play();
    myPlayer2.play();
    myPlayer3.play();
    myPlayer4.play();
    myPlayer5.play();
    myPlayer6.play();
    
    mySound.load("videos/m1.mp3");
    mySound.play();
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    myPlayer1.update();
    myPlayer2.update();
    myPlayer3.update();
    myPlayer4.update();
    myPlayer5.update();
    myPlayer6.update();
    
    
	fingersFound.clear();
	
	//here is a simple example of getting the hands and drawing each finger and joint
	//the leap data is delivered in a threaded callback - so it can be easier to work with this copied hand data
	
	//if instead you want to get the data as it comes in then you can inherit ofxLeapMotion and implement the onFrame method.
	//there you can work with the frame data directly.
    
    
    
    //Option 1: Use the simple ofxLeapMotionSimpleHand - this gives you quick access to fingers and palms.
    
    
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for(int i = 0; i < simpleHands.size(); i++){
            for (int f=0; f<5; f++) {
                int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp; // metacarpal
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip; // proximal
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip; // distal
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip; // fingertip
                fingersFound.push_back(id);
            }
        }
    }
    
    if(simpleHands.size()){
        fingerPos = simpleHands[0].fingers[INDEX].tip;
        cout<<"finger Position"<<endl;
        cout<<fingerPos.x<<endl;
        cout<<fingerPos.y<<endl;
        cout<<fingerPos.z<<endl;
        finPos = ofVec2f(simpleHands[0].fingers[INDEX].tip.x, simpleHands[0].fingers[INDEX].tip.y);
        if(ofDist(finPos.x, finPos.y, line0.x, line0.y)<10){
            stage = 1;
        }else if(ofDist(finPos.x, finPos.y, line1.x, line1.y)<20){
            stage = 2;
        }else if(ofDist(finPos.x, finPos.y, line2.x, line2.y)<45){
            stage = 3;
        }else if(ofDist(finPos.x, finPos.y, line3.x, line3.y)<68.5){
            stage = 4;
        }else if(ofDist(finPos.x, finPos.y, line4.x, line4.y)<117.5){
            stage = 5;
        }else if(ofDist(finPos.x, finPos.y, line5.x, line5.y)<195){
            stage = 6;
        }
    }
    
    
    //Option 2: Work with the leap data / sdk directly - gives you access to more properties than the simple approach
    //uncomment code below and comment the code above to use this approach. You can also inhereit ofxLeapMotion and get the data directly via the onFrame callback.
    /*
     vector <Hand> hands = leap.getLeapHands();
     if( leap.isFrameNew() && hands.size() ){
     
     //leap returns data in mm - lets set a mapping to our world space.
     //you can get back a mapped point by using ofxLeapMotion::getMappedofPoint with the Leap::Vector that tipPosition returns
     leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
     leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
     leap.setMappingZ(-150, 150, -200, 200);
     
     fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
     
     for(int i = 0; i < hands.size(); i++){
     for(int j = 0; j < 5; j++){
     ofPoint pt;
     
     const Finger & finger = hands[i].fingers()[ fingerTypes[j] ];
     
     //here we convert the Leap point to an ofPoint - with mapping of coordinates
     //if you just want the raw point - use ofxLeapMotion::getofPoint
     pt = leap.getMappedofPoint( finger.tipPosition() );
     pt = leap.getMappedofPoint( finger.jointPosition(finger.JOINT_DIP) );
     
     fingersFound.push_back(finger.id());
     }
     }
     }
     */
    
	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.
	leap.markFrameAsOld();
}

//--------------------------------------------------------------
void ofApp::draw(){

    switch (stage) {
        case 1:
           myPlayer1.draw(0,0,1024,568);
            //ofBackground(255, 0, 0);
            break;
        case 2:
            myPlayer2.draw(0,0,1024,568);
            //ofBackground(150, 0, 0);
            break;
        case 3:
            myPlayer3.draw(0,0,1024,568);
            //ofBackground(0, 150, 0);
            break;
        case 4:
            myPlayer4.draw(0,0,1024,568);
            //ofBackground(0, 255, 0);
            break;
        case 5:
            myPlayer5.draw(0,0,1024,568);
            //ofBackground(0, 0, 150);
            break;
        case 6:
            myPlayer6.draw(0,0,1024,568);
            //ofBackground(0, 0, 255);
            break;
            
        default:
            break;
    }
//    ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30),  OF_GRADIENT_BAR);
//
//    ofSetColor(200);
//    ofDrawBitmapString("ofxLeapMotion - Example App\nLeap Connected? " + ofToString(leap.isConnected()), 20, 20);
//
//    cam.begin();
//
//    ofPushMatrix();
//    ofRotate(90, 0, 0, 1);
//    ofSetColor(20);
//    ofDrawGridPlane(800, 20, false);
//    ofPopMatrix();
//
//
//    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
//
//    for(int i = 0; i < simpleHands.size(); i++){
//        bool isLeft        = simpleHands[i].isLeft;
//        ofPoint handPos    = simpleHands[i].handPos;
//        ofPoint handNormal = simpleHands[i].handNormal;
//
//        ofSetColor(0, 0, 255);
//        ofDrawSphere(handPos.x, handPos.y, handPos.z, 20);
//        ofSetColor(255, 255, 0);
//        ofDrawArrow(handPos, handPos + 100*handNormal);
//
//        for (int f=0; f<5; f++) {
//            ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;  // metacarpal
//            ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;  // proximal
//            ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;  // distal
//            ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;  // fingertip
//
//            ofSetColor(0, 255, 0);
//            ofDrawSphere(mcp.x, mcp.y, mcp.z, 12);
//            ofDrawSphere(pip.x, pip.y, pip.z, 12);
//            ofDrawSphere(dip.x, dip.y, dip.z, 12);
//            ofDrawSphere(tip.x, tip.y, tip.z, 12);
//
//            ofSetColor(255, 0, 0);
//            ofSetLineWidth(20);
//            ofLine(mcp.x, mcp.y, mcp.z, pip.x, pip.y, pip.z);
//            ofLine(pip.x, pip.y, pip.z, dip.x, dip.y, dip.z);
//            ofLine(dip.x, dip.y, dip.z, tip.x, tip.y, tip.z);
//        }
//    }
//    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
}
