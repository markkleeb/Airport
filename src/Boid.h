/*
 *  Boid.h
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  Extended by Mark Kleeback and Ali Sajjadi on 3/7/2012
 *
 */

#ifndef BOID_H
#define BOID_H

#include "ofMain.h"
#include "ofxCvBlob.h"
#include "ofxCvContourFinder.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Path.h"


class Boid {
    
public:
	Boid();
	
	void update();
	void draw();
    void seek(ofPoint target);
    void arrive(ofPoint target);
    void follow(Path* p);
    ofPoint getNormalPoint(ofPoint a, ofPoint b, ofPoint c);
    ofPoint steer(ofPoint target, bool slowdown);
    void intersects(ofxCvContourFinder& _cf, Path* _path);
    
    int objAvoidScalar;
    int counter;
    
    float r;
	float maxforce;
	float maxspeed;
    float wandertheta;
    float record;
    
    ofImage i;
    
    ofPoint loc;
	ofPoint vel;
	ofPoint acc;
    ofPoint normal;
    ofPoint target;
    ofPoint predictLoc;
    ofPoint dir;
    
    bool avoidObject;
    bool projected;
    bool debug;    
    
    vector<ofPoint> p;
};

#endif