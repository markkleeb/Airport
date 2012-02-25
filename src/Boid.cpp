/*
 *  Boid.cpp
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "Boid.h"

Boid::Boid() {

    loc.x = 600;
	loc.y = 400;
    vel.x = ofRandom(-2, 2);
    vel.y = ofRandom(-2, 2);
    
	acc = -0.01;
	
	cout << loc.x << ", " << loc.y << endl;
    r = 3.0;
    maxspeed = 2;
    maxforce = 0.1;
}


// Method to update location
void Boid::update() {
    
    
  
   // vel += acc;   // Update velocity
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed
   
    loc += vel;
    
    loc.x = ofClamp(loc.x, 0, ofGetWindowWidth());
    loc.y = ofClamp(loc.y, 0, ofGetWindowHeight());
    
    acc = 0;  // Reset accelertion to 0 each cycle
	
//	if (loc.x < -r) loc.x = ofGetWidth()+r;
//    if (loc.y < -r) loc.y = ofGetHeight()+r;
//    if (loc.x > ofGetWidth()+r) loc.x = -r;
//    if (loc.y > ofGetHeight()+r) loc.y = -r;
}


void Boid::draw() {
    // Draw a triangle rotated in the direction of velocity
    //float theta = vel.heading2D() + radians(90);
	
    
    if(loc.x == 0 || loc.x == ofGetWindowWidth()) vel.x *= -1;
    if(loc.y == 0 || loc.y == ofGetWindowHeight()) vel.y *= -1;

	

	
	float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
	float heading2D = ofRadToDeg(theta)+90;
	
	ofEnableAlphaBlending();
    ofSetColor(0, 0, 0);
    ofFill();
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    ofRotateZ(heading2D);
	ofBeginShape();
    ofVertex(0, -r*2);
    ofVertex(-r, r*2);
    ofVertex(r, r*2);
    ofEndShape(true);
    ofPopMatrix();
	ofDisableAlphaBlending();
}

void Boid::intersects(Blob b){
    
    ofPoint heading = loc + vel;  // A vector pointing from the location to where the boid is heading
    float d = ofDist(loc.x, loc.y, heading.x, heading.y); // Distance from the target is the magnitude of the vector
	heading /= d;
    
    ofSetColor(255, 0, 0);
    ofLine(loc.x, loc.y, heading.x, heading.y);
    
    
    if(heading.x >=  b.loc.x && heading.x <= b.loc.x +10) vel.x +=2.1;
    if(heading.x <= b.loc.x && heading.x >= b.loc.x -10) vel.x -=2.1;
    if(heading.y >= b.loc.y && heading.y <= b.loc.y +10) vel.y +=2.1;
    if(heading.y <= b.loc.y && heading.y >= b.loc.y -10) vel.y -=2.1;
    if(heading.x > ofGetWindowWidth() || heading.x < 0) vel.x *= -1.1;
    if(heading.y > ofGetWindowHeight() || heading.y < 0) vel.y *= -1.1;
    
    //instead of adding to vel vectors, maybe applyForce laterally?

    
    
    else{
        return;
    }
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed

    
    
}
    
    
    
    


