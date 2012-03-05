#pragma once

#include "ofMain.h"
#include "Boid.h"
#include "Blob.h"
#include "Boundaries.h"
/* KINECTLESS
#include "ofxOpenCv.h"
#include "ofxKinect.h"
*/

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
       // void exit();
    
        void kinectImage();
    
        void drawPointCloud();
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        /* KINECTLESS
     
        ofxKinect kinect;
        */
        vector<Boid> boids;
        vector<Blob> blobs;
        vector<Boundaries> bounds;
    
        /* KINECTLESS

        ofxCvColorImage colorImg;
        
        ofxCvGrayscaleImage grayImage; // grayscale depth image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
        
        ofxCvContourFinder contourFinder;
        */
        bool bThreshWithOpenCV;
        bool bDrawPointCloud;
        bool kinectOn;
        
        int nearThreshold;
        int farThreshold;
        
        int angle;
        
        // used for viewing the point cloud
        ofEasyCam easyCam;
    
private:
    void capture();
    bool doCapture;
    int framenum;
};
