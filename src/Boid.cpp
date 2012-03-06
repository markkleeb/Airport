/*
 *  Boid.cpp
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "Boid.h"
#include "Path.h"

Boid::Boid() {

    loc.x = 800;
	loc.y = 700;
    //vel.x = ofRandom(-2, 2);
    //vel.y = ofRandom(-2, 2);
   
    
	acc = 0;
	
    r = 5.0;
    maxspeed = 1.5;
    maxforce = 0.1;
     vel = ofPoint(maxspeed, 0);
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
	
    
//wrap borders    
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
    ofSetColor(255, 255, 255);
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

void Boid::intersects(ofxCvContourFinder& _cv, Path* _path){
    
    follow( _path);
    
  //  ofPoint f = follow( _path );
  
   // acc = acc + f;
    
  //  cout<< "FORCE = " << f.x << " , " << f.y << "\n";
    
    
    ofPoint heading = loc + vel*25;  // A vector pointing from the location to where the boid is heading
    
    
    for ( int i = 0; i < _cv.blobs.size(); i++ ) {
        ofxCvBlob temp = _cv.blobs[i];
        ofPolyline l;
        l.addVertexes(temp.pts);
        
        if(l.inside(heading))
        {   //vel *= -1;
            ofVec2f force = heading - _cv.blobs[i].centroid;
            acc = acc + force.normalize();
            cout << "bounce!\n";
        }        
        /*else{
            wander();
            cout << "wandering!\n";
       }*/ 
        
        
    }    
    
}

void Boid::follow(Path* p) {
    ofPoint predict = vel;
    Path::normalize(&predict);
    predict *= 25;
    predictLoc = loc + predict;
    
    
	
    // Now we must find the normal to the path from the predicted location
    // We look at the normal for each line segment and pick out the closest one
    
    record = 1000000;  // Start with a very high record distance that can easily be beaten
	
    // Loop through all points of the path
    for (int i = 0; i < p->points.size()-1; i++) {
		
		// Look at a line segment
		ofPoint a = p->points[i];
		ofPoint b = p->points[i+1];
		
		// Get the normal point to that line
		ofPoint normal = getNormalPoint(predictLoc,a,b);
		
		// Check if normal is on line segment
		float da = ofDist(normal.x, normal.y, a.x, a.y);
		float db = ofDist(normal.x, normal.y, b.x, b.y);
		ofPoint line = b-a;
        
		// If it's not within the line segment, consider the normal to just be the end of the line segment (point b)
		if (da + db > Path::mag(&line)+1.0) {
			normal = b;
		}
		
		// How far away are we from the path?
		float d = ofDist(predictLoc.x, predictLoc.y, normal.x, normal.y);
		// Did we beat the record and find the closest line segment?
		if (d < record) {
			record = d;
			// If so the target we want to steer towards is the normal
			target = normal;
			
			// Look at the direction of the line segment so we can seek a little bit ahead of the normal
			dir = line;
			Path::normalize(&dir);
			// This is an oversimplification
			// Should be based on distance to path & velocity
			dir*=10;
		}
    }
	
    // Only if the distance is greater than the path's radius do we bother to steer
    if (record > p->radius) {
		target += dir;
		seek(target);			
    }
    
    
}
           
ofPoint Boid::getNormalPoint(ofPoint p, ofPoint a, ofPoint b) {
	
    // Vector from a to p
    ofPoint ap = p - a;
	
    // Vector from a to b
    ofPoint ab = b - a;
	
	Path::normalize(&ab); // Normalize the line
	
    // Project vector "diff" onto line by using the dot product
    ab *= Path::dotproduct(ab, ap);
	
    return a + ab;
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


ofPoint Boid::steer(ofPoint target, bool slowdown) {
    ofPoint steer;  // The steering vector
    ofPoint desired = target - loc;  // A vector pointing from the location to the target
    float d = ofDist(target.x, target.y, loc.x, loc.y); // Distance from the target is the magnitude of the vector
    
	// If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
		
		desired /= d; // Normalize desired
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((slowdown) && (d < 100.0f)) {
			desired *= maxspeed * (d/100.0f); // This damping is somewhat arbitrary
		} else {
			desired *= maxspeed;
		}
		// Steering = Desired minus Velocity
		steer = desired - vel;
		steer.x = ofClamp(steer.x, -maxforce, maxforce); // Limit to maximum steering force
		steer.y = ofClamp(steer.y, -maxforce, maxforce); 
    }
    return steer;
}


void Boid::seek(ofPoint target) {
    acc += steer(target, false);
}

void Boid::arrive(ofPoint target) {
    acc += steer(target, true);
}


