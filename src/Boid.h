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


class Boid {
public:
	Boid();
	
	void update();
	void draw();
    void wander();
	
	ofPoint loc;
	ofPoint vel;
	ofPoint acc;
	float r;
	float maxforce;
	float maxspeed;
    float wandertheta;
    float checkL;
    
    bool projected;
    
    vector<ofPoint> p;
    
    ofxCvContourFinder contourFinder;
 
    ofPoint overlap(ofxCvBlob b1, ofxCvBlob b2);
    
    ofPoint steer(ofPoint target, Boolean slowdown);
    
    
    void intersects(ofPolyline b);
};

#endif