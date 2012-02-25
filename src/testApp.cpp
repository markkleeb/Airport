#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 255, 0 );
    
    ofSetFrameRate(36);
	
	framenum=0;
	doCapture=false;
	
	
		Boid b;
		boids.push_back( b );
	
    for(int i = 0; i < 10; i ++){
        
        Blob b;
        blobs.push_back( b );
        
        
    }
    

}

//--------------------------------------------------------------
void testApp::update(){

    for(int i=0; i<boids.size(); i++)
	{
	
		boids[i].update();
	
    
    for(int j = 0; j<blobs.size(); j++)
    {
        
        boids[i].intersects(blobs[j]);
        
        
    }
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofNoFill();
	ofCircle(mouseX, mouseY, 20);
    
    
    cout << " " << ofGetFrameNum();
    
    if(ofGetFrameNum()%120 == 1){
        Boid b;
		boids.push_back( b );
    }
	
	for(int i=0; i<boids.size(); i++) {
		boids[i].draw();
	}
    
    for(int i=0; i<blobs.size(); i ++){
        blobs[i].draw();
    }
	capture();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
   
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    
   
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    ofSetColor(255, 0, 0);
    ofCircle(mouseX, mouseY, 20);
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::capture() {
	if(doCapture && ofGetFrameNum() % 4 == 0)
	{
		char filename[255];
		sprintf(filename, "frame%05d.png", framenum++);
		ofSaveScreen(filename);
	}
}


