#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    startX = 1100;
    startY = 650;
    ofSetFrameRate(60);
	
    ofSetLogLevel(OF_LOG_VERBOSE);
	
	// enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	kinect.open();
	
#ifdef USE_TWO_KINECTS
	kinect2.init();
	kinect2.open();
#endif
	
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 230;
	farThreshold = 90;
	bThreshWithOpenCV = true;
	

	
	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
	
	// start from the front
	bDrawPointCloud = false;

    
    
	framenum=0;
	doCapture=false;
    
    newPath();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofBackground(0, 0, 0);
    
    kinect.update();
    
    
    // there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		
		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		} else {
			
			// or we do it ourselves - show people how they can work with the pixels
			unsigned char * pix = grayImage.getPixels();
			
			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}
		}
		
		// update the cv images
		grayImage.flagImageChanged();
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 20, false);
        
	}

    

    for(int i=0; i<boids.size(); i++)
	{
	
        boids[i].intersects(contourFinder, path);
		boids[i].update();
            
        
        if(boids[i].loc.x < 50 && boids[i].loc.y < 200){
            boids.erase(boids.begin() + i);
        }
      
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    path->draw();
    
    ofSetColor(255, 255, 255);
    
	kinectImage(); 
    
    if(ofGetFrameNum()%300 == 1){
        Boid b;
		boids.push_back( b );

    }
	
	for(int i=0; i<boids.size(); i++) {
		boids[i].draw();
        
        if(boids[i].debug){
            for(int i=0; i<contourFinder.blobs.size(); i++){
                
                ofPushMatrix();
                ofTranslate(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
                ofSetColor(0, 255, 0);
                ofEllipse(0, 0, 10, 10);
                ofPopMatrix();
                
                
            }

        }
        
        
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
		case ' ':
			bThreshWithOpenCV = !bThreshWithOpenCV;
			break;
			
		case'p':
            if (kinectOn) {
                kinectOn = false;
                for(int i = 0; i < boids.size(); i++)
                {
                    boids[i].debug = false;
                }
            } else {
                kinectOn = true;
                for(int i = 0; i < boids.size(); i++)
                {
                    boids[i].debug = true;
                }
            }
			break;
			
		case '>':
		case '.':
			farThreshold ++;
            cout<<"Threshold: "<<farThreshold<<"\n";
			if (farThreshold > 255) farThreshold = 255;
			break;
			
		case '<':
		case ',':
			farThreshold --;
            
            cout<<"Threshold: "<<farThreshold<<"\n";
			if (farThreshold < 0) farThreshold = 0;
			break;
			
		case '+':
		case '=':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
			
		case '-':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
			
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
			
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
        
        case 'n':
            boids.push_back(Boid());
            break;
			
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
            
        case 'd':
            for(int i = 0; i < boids.size(); i++)
            {
                boids[i].debug = false;
            }
			break;
            
	}


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


void testApp::drawPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 2;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect.getDistanceAt(x, y) > 0) {
				mesh.addColor(kinect.getColorAt(x,y));
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
			}
		}
	}
	glPointSize(3);
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards' 
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	glEnable(GL_DEPTH_TEST);
	mesh.drawVertices();
	glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
}

void testApp::kinectImage(){

    
    if(kinectOn) {
        
        contourFinder.draw(0,0);    
        
        // draw instructions
        ofSetColor(255, 255, 255);
        
        stringstream reportStream;
        reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
        << ofToString(kinect.getMksAccel().y, 2) << " / "
        << ofToString(kinect.getMksAccel().z, 2) << endl
        << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
        << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
        << "set near threshold " << nearThreshold << " (press: + -)" << endl
        << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
        << ", fps: " << ofGetFrameRate() << endl
        << "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl
        << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl;
        
        ofDrawBitmapString(reportStream.str(),20,790);

    }
    
}


void testApp::newPath() {
    
    path = new Path();
    path->addPoint(startX, startY);
    path->addPoint(150, 650);
    path->addPoint(150, 400);
    path->addPoint(1000, 400);
    path->addPoint(1000, 150);
    path->addPoint(0, 150);
    
    
}

