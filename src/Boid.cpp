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
    
	acc = 0;
	
    r = 5.0;
    maxspeed = 2;
    maxforce = 0.1;
    checkL = 30;
    wandertheta = 0.0;
    
}


// Method to update location
void Boid::update() {
    
    
  
   vel += acc;   // Update velocity
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
    ofSetColor(0, 0, 255);
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

void Boid::intersects(ofPolyline l){
    
    projected = false;
    
    float checkLength = checkL*vel.length();
    
    ofPoint projection;
    ofPoint force;
    ofPoint lateral;
    
    ofPoint forward = vel.normalize();
    ofPoint ray = forward;
    ray = ray*checkLength;
    lateral = ray;
    lateral.set(lateral.y, -lateral.x, 0);
    lateral = lateral*r;
    
    
    p.push_back(ofPoint(lateral.x, lateral.y));
    p.push_back(ofPoint(-lateral.x, -lateral.y));
    p.push_back(ofPoint(ray.x-lateral.x,ray.y-lateral.y));
    p.push_back(ofPoint(ray.x+lateral.x,ray.y+lateral.y));
    

    
    

  
   ofxCvBlob check;
    
    check.centroid.x = loc.x;
    check.centroid.y = loc.y;
    
    for(int i = 0; i < p.size(); i++){
        check.pts.push_back(p[i]);
    }
    
    
    
    
    ofPoint heading = loc + vel;  // A vector pointing from the location to where the boid is heading
    float d = ofDist(loc.x, loc.y, heading.x, heading.y); // Distance from the target is the magnitude of the vector
	heading /= d;
    
    ofSetColor(255, 0, 0);
    ofLine(loc.x, loc.y, heading.x, heading.y);
  
    for ( int i = 0; i < contourFinder.blobs.size(); i++ ) {
        
        projection = overlap(check,contourFinder.blobs[i]);
        if ( (projection.x != 0) || (projection.y != 0) ) { //overlapping so steer away
            projected = true;
            projection.normalize();
            force = lateral;
            force.normalize();
            force *= projection.dot(force) ;
            force.limit(maxforce);
            acc+=force;
        }
    }
    if ( projected == false ) { //if there is no objects to steer around, wander
        wander();
    }
    

    


    
    
//   if(l.inside(ray))
//    {vel *= -1;
//    }
  //  if(heading.x >=  b.loc.x && heading.x <= b.loc.x +10 && heading.y == b.loc.y) vel.x +=2.1;
  //  if(heading.x <= b.loc.x && heading.x >= b.loc.x -10 && heading.y == b.loc.y) vel.x -=2.1;
  //  if(heading.y >= b.loc.y && heading.y <= b.loc.y +10 && heading.x == b.loc.x) vel.y +=2.1;
  //  if(heading.y <= b.loc.y && heading.y >= b.loc.y -10 && heading.x == b.loc.x) vel.y -=2.1;
  //  if(heading.x > ofGetWindowWidth() || heading.x < 0) vel.x *= -1.1;
  //  if(heading.y > ofGetWindowHeight() || heading.y < 0) vel.y *= -1.1;
    
    //instead of adding to vel vectors, maybe applyForce laterally?

    
    
//    else{
//        return;
//    }
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed

    
    
}


void Boid::wander() {
    float wanderR = 16.0f;         // Radius for our "wander circle"
    float wanderD = 50.0f;         // Distance for our "wander circle"
    float change = 0.3f;//0.25f;
    wandertheta += ofRandom(-change, change); // Randomly change wander theta
    
    // Now we have to calculate the new location to steer towards on the wander circle
    ofPoint circleloc;
    circleloc.set(vel.x, vel.y);  // Start with velocity
    circleloc.normalize();            // Normalize to get heading
    circleloc *= wanderD;          // Multiply by distance
    circleloc += loc;               // Make it relative to boid's location
    
    ofPoint circleOffSet;
    circleOffSet.set(wanderR*cos(wandertheta),wanderR*sin(wandertheta));
    ofPoint target = circleloc + circleOffSet;
    
    acc += steer(target,false);  // Steer towards it
    
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A method that calculates a steering vector towards a target
// Takes a second argument, if true, it slows down as it approaches the target

ofPoint Boid::steer(ofPoint target, Boolean slowdown) {
    ofPoint steer;  // The steering vector
    ofPoint desired = (target - loc);  // A vector pointing from the location to the target
    float d = desired.length(); // Distance from the target is the magnitude of the vector
    // If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
        // Normalize desired
        desired.normalize();
        // Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
        if ((slowdown) && (d < 100.0f)) desired *= (maxspeed*(d/100.0f)); // This damping is somewhat arbitrary
        else desired *= (maxspeed);
        // Steering = Desired minus Velocity
        steer = desired - vel;
        //steer.add(new PVector(0,1f)); //pull down
        steer.limit(maxforce);  // Limit to maximum steering force
        
    } else {
        steer = ofPoint(0,0);
    }
    return steer;
}

    

    
ofPoint Boid::overlap(ofxCvBlob ob1, ofxCvBlob ob2) { //ob1 is one that is projected (moves)
    
    ofPoint nor,pt,projection;
    float low1,high1,low2,high2,dt; 
    projection = ofPoint(900000000,0);
    
    for (int q = 0; q < ob1.pts.size(); q++ ) {
        if ( q == (ob1.pts.size()-1) ) {
            nor = ob1.pts[0] - ob1.pts[q];
        }
        else {
            nor = ob1.pts[q] - ob1.pts[q+1];
        }
        nor.set(-nor.y,nor.x,0); //rotate 90 degrees
        nor.normalize();
        
        //set the values so any value will work
        low1 = 9000000;
        high1 = -9000000;
        for ( int i = 0; i < ob1.pts.size(); i++ ) {
            pt = ob1.pts[i] + ofPoint(ob1.centroid.x,ob1.centroid.y);
            dt = pt.dot(nor);
            if ( dt < low1 ) { low1 = dt; }
            if ( dt > high1 ) { high1 = dt; }
        }
        low2 = 90000000;
        high2 = -900000000;
        for ( int i = 0; i < ob2.pts.size(); i++ ) {
            pt = ob2.pts[i] + ofPoint(ob2.centroid.x,ob2.centroid.y);
            dt = pt.dot(nor);
            if ( dt < low2 ) { low2 = dt; }
            if ( dt > high2 ) { high2 = dt; }
        }
        //find projection using min overlap of low1-high1 and low2-high2
        //ob1 is the one that is projected (moves)
        float mid1,mid2;
        mid1 = 0.5f*(low1+high1);
        mid2 = 0.5f*(low2+high2);
        if ( mid1 < mid2 ) {
            if ( high1 < low2 ) { //no overlap
                return (ofPoint(0,0)); //return a null vector
            }
            else { //test to see if projection is smallest
                if ( (high1-low2) < projection.length() ) { //new smallest projection found
                    projection = nor;
                    projection.normalize();
                    projection *=(-(high1-low2));
                }
            }
        }
        else {
            if ( low1 > high2 ) { //no overlap
                return (ofPoint(0,0)); //return a null vector
            }
            else {
                if ( (high2-low1) < projection.length() ) { //new smallest projection found
                    projection = nor;
                    projection.normalize();
                    projection *= (high2-low1);
                }
            }
        }
    }
    
    //do same for ob2/////////////////////////////////////////////////////////////////////////////
    for ( int q = 0; q < ob2.pts.size(); q++ ) {
        //println(ob1.points.size());
        if ( q == (ob2.pts.size()-1) ) {
            nor = ob2.pts[0] - ob2.pts[q];
        }
        else {
            nor = ob2.pts[q] - ob2.pts[q+1];
        }
        nor.set(-nor.y,nor.x,0); //rotate 90 degrees
        nor.normalize();
        nor *= 100;
        nor.normalize();
        //set the values so any value will work
        low1 = 90000000;
        high1 = -900000000;
        for ( int i = 0; i < ob1.pts.size(); i++ ) {
            pt = ob1.pts[i] + ofPoint(ob1.centroid.x, ob1.centroid.y);
            dt = pt.dot(nor);
            if ( dt < low1 ) { low1 = dt; }
            if ( dt > high1 ) { high1 = dt; }
        }
        low2 = 900000000;
        high2 = -900000000;
        for ( int i = 0; i < ob2.pts.size(); i++ ) {
            pt = ob2.pts[i] + ofPoint(ob2.centroid.x,ob2.centroid.y);
            dt = pt.dot(nor);
            if ( dt < low2 ) { low2 = dt; }
            if ( dt > high2 ) { high2 = dt; }
        }
        //find projection using min overlap of low1-high1 and low2-high2
        //ob1 is the one that is projected (moves)
        float mid1,mid2;
        mid1 = 0.5f*(low1+high1);
        mid2 = 0.5f*(low2+high2);
        if ( mid1 < mid2 ) {
            if ( high1 < low2 ) { //no overlap
                return (ofPoint(0,0)); //return a null vector
            }
            else { //test to see if projection is smallest
                if ( (high1-low2) < projection.length() ) { //new smallest projection found
                    projection = nor;
                    projection.normalize();
                    projection *= (-(high1-low2));
                }
            }
        }
        else {
            if ( low1 > high2 ) { //no overlap
                return (ofPoint(0,0)); //return a null vector
            }
            else {
                if ( (high2-low1) < projection.length()) { //new smallest projection found
                    projection = nor;
                    projection.normalize();
                    projection *= ((high2-low1));
                }
            }
        }
    }
    
    return projection;
}


    


