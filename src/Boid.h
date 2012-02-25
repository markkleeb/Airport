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

class Boid {
public:
	Boid();
	
	void update();
	void draw();
	
	ofPoint loc;
	ofPoint vel;
	ofPoint acc;
	float r;
	float maxforce;
	float maxspeed;
    
    
    void intersects(Blob b);
};

#endif