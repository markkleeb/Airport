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
  	ofPoint loc;
	ofPoint vel;
	ofPoint acc;
	float r;
	float maxforce;
	float maxspeed;
  
    
public:
	Boid();
    Boid(float _x, float _y);

	void update();
	void draw();
    void intersects(Blob b);
};

#endif