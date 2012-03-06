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

    loc.x = ofGetWindowWidth()/2;
	loc.y = ofGetWindowHeight()/2;
    vel.x = 0;
    vel.y = 0;
	acc = 0;
    
    r = 3.0;
    
    maxspeed = 2;
    maxforce = 0.5;
    
    
}

Boid::Boid(float _x, float _y) {
    
    loc.x = _x;
	loc.y = _y;
    vel.x = 0;
    vel.y = 0;
	acc = 0;
    
    r = 3.0;
    
    maxspeed = 2;
    maxforce = 0.5;
}


void Boid::update() {
    
    
    vel += acc;
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed
   
    loc += vel;
    
    loc.x = ofClamp(loc.x, 0, ofGetWindowWidth());
    loc.y = ofClamp(loc.y, 0, ofGetWindowHeight());
    
    acc = 0;  // Reset accelertion to 0 each cycle

}


void Boid::draw() {

	

	
	float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
	float heading2D = ofRadToDeg(theta)+90;

        // DRAW BOID SHAPE
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
    

    
    
        // DRAW BOID HEADING AND VECTORS -- REMOVE FOR RELEASE
    ofPoint heading = loc + vel*maxspeed*10;  // A vector pointing from the location to where the boid is heading
    ofSetColor(255, 255, 255);
    ofFill();
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    ofCircle(0, 0, 5.0);
    ofSetColor(0, 0, 255);
    ofLine(0,0,vel.x*maxspeed*10, vel.y*maxspeed*10);
    ofSetColor(255, 104, 31);
    ofPopMatrix();
    ofCircle(heading.x, heading.y, 2.0);
    
    ofSetColor(255, 0, 0);
}

void Boid::intersects(Blob b){
    
    ofPoint heading = loc + vel*maxspeed*10;  // A vector pointing from the location to where the boid is 
    

    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed

}