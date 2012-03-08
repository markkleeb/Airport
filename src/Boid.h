/*
 *  Boid.h
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#ifndef BOID_H
#define BOID_H

#include "ofMain.h"
#include "Blob.h"
#include <list>
#include "ofxCvBlob.h"
#include "ofxCvContourFinder.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Path.h"


class Boid {
    
        //INSTANCE VARIABLES
    ofPoint loc;
	ofPoint vel;
	ofPoint acc;
    
    ofPoint normal;
    ofPoint target;
    ofPoint predictLoc;
    ofPoint dir;
	float r;
	float maxforce;
	float maxspeed;
    float wandertheta;
    float record;
    
public:
	Boid();
    ~Boid();
	
	void update();
	void draw();
    void seek(ofPoint target);
    void arrive(ofPoint target);
    void wander();
	

    void start;
    
    void follow(Path* p);
    ofPoint getNormalPoint(ofPoint a, ofPoint b, ofPoint c);
    
    bool projected;
    
    vector<ofPoint> p;
    
 
  //  ofPoint overlap(ofxCvBlob b1, ofxCvBlob b2);
    
    ofPoint steer(ofPoint target, bool slowdown);
    
    
    void intersects(ofxCvContourFinder& _cf, Path* _path);
};

#endif