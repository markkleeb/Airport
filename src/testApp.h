#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Path.h"
#include "Boid.h"



class testApp : public ofBaseApp{

    int                 startX;
    int                 startY;
    
public:
    
    void    setup();
    void    update();
    void    draw();
    void    keyPressed         (int key);
    void    keyReleased        (int key);
    void    mouseMoved         (int x, int y );
    void    mouseDragged       (int x, int y, int button);
    void    mousePressed       (int x, int y, int button);
    void    mouseReleased      (int x, int y, int button);
    void    windowResized      (int w, int h);
    void    dragEvent          (ofDragInfo dragInfo);
    void    gotMessage         (ofMessage msg);
    
    void    kinectImage();
    void    drawPointCloud();
    
    void    newPath();
    
    ofxKinect           kinect;
    vector  <Boid>      boids;
    vector  <ofxCvBlob> cvBlobs;    
    Path*               path;
    
    ofxCvColorImage     colorImg;
        
    // grayscale depth image
    ofxCvGrayscaleImage grayImage; 
        
    // the near thresholded image
    ofxCvGrayscaleImage grayThreshNear; 
       
    // the far thresholded image
    ofxCvGrayscaleImage grayThreshFar;         
    ofxCvContourFinder  contourFinder;
    ofxCvBlob           CvBlob;

    bool                bThreshWithOpenCV;
    bool                bDrawPointCloud;
    bool                kinectOn;

    int                 nearThreshold;
    int                 farThreshold;
    int                 angle;
        
    // used for viewing the point cloud
    ofEasyCam           easyCam;
    
private:
    void    capture();
    bool    doCapture;
    int     framenum;
};
