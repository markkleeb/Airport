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

Boid::Boid(float _x, float _y) {
    
    loc.x = _x;
	loc.y = _y;
    vel.x = ofRandom(-2, 2);
    vel.y = ofRandom(-2, 2);
    
	acc = -0.01;
	
	cout << loc.x << ", " << loc.y << endl;
    r = 3.0;
    maxspeed = 2;
    maxforce = 0.1;
}

Boid::Boid(float _x, float _y, float _vX, float _vY) {
    
    loc.x = _x;
	loc.y = _y;
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

}


void Boid::draw() {
    // Draw a triangle rotated in the direction of velocity
    //float theta = vel.heading2D() + radians(90);
	
    
    if(loc.x == 0 || loc.x == ofGetWindowWidth()) 
    {
        vel.x *= -1;
        cout<<"WALL X\n";
    }
    if(loc.y == 0 || loc.y == ofGetWindowHeight()){
        vel.y *= -1;
        cout<<"WALL Y\n";
    }
	

	
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
    
    ofPoint heading = loc + vel*20;  // A vector pointing from the location to where the boid is heading
    ofSetColor(255, 255, 255);
    ofFill();
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    ofCircle(0, 0, 5.0);
    ofSetColor(0, 0, 255);
    ofLine(0,0,vel.x*20, vel.y*20);
    ofSetColor(255, 104, 31);
    ofPopMatrix();
    ofCircle(heading.x, heading.y, 2.0);
}

void Boid::intersects(Blob b){
    
    ofPoint heading = loc + vel;  // A vector pointing from the location to where the boid is heading
        //float d = ofDist(loc.x, loc.y, heading.x, heading.y); // Distance from the target is the magnitude of the vector
    
        //cout<<"Heading X : "<<heading.x<<" Heading Y : "<<heading.y<<" Distance : "<<d;
        //heading /= d;
        //cout<<" heading x after : "<<heading.x<<" heading y after: "<<heading.y<<"\n";

    
    if(heading.x > b.loc.x && heading.x <= b.loc.x+b.r) 
    {
        vel.x +=2.1;
        cout<<"CASE 1\n";
    }
    if(heading.x <= b.loc.x && heading.x >= b.loc.x -b.r) {
        vel.x -=2.1;
        cout<<"CASE 2\n";

    }
    if(heading.y >= b.loc.y && heading.y <= b.loc.y +b.r) {
        vel.y +=2.1;
        cout<<"CASE 3\n";

    }
    if(heading.y <= b.loc.y && heading.y >= b.loc.y -b.r) {
        vel.y -=2.1;
        cout<<"CASE 4\n";
    }
    if(heading.x > ofGetWindowWidth() || heading.x < 0) {
        vel.x *= -1.1;
        cout<<"CASE 5\n";

    }
    if(heading.y > ofGetWindowHeight() || heading.y < 0) {
        vel.y *= -1.1;
        cout<<"CASE 6\n";

    }
    
    //instead of adding to vel vectors, maybe applyForce laterally?

    
    
    else{
        return;
    }
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed

    
    
}