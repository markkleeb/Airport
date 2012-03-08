/*
 *  Boid.cpp
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  Extended by Mark Kleeback and Ali Sajjadi on 3/6/12
 *  
 */

#include "Boid.h"
#include "Path.h"

Boid::Boid() {

    // Initialize our location for our take-off point
    loc.x = 1001;
	loc.y = 651;  
    
    // Acceleration vector is zero at start, the functions will decide where to go
	acc = 0;
	
    r = 5.0;
    
    // Maximum speed of the plane
    maxspeed = 2;
    maxforce = 0.1;
    
    // Velocity vector is set to start at maximum speed
    vel = ofPoint(-maxspeed, 0);
    
    debug = false;
    
    // Image of our airplane to be loaded and resize
    i.loadImage("airplane.png");
    i.resize(25,30);
    
    counter = 0;
    avoidObject = false;
    
}


// Method to update location
void Boid::update() {
    
    // Update velocity
    vel += acc;   
    
    // Limit speed
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);    
    
    // Update location according to our velocity vector
    loc += vel;     
    
    // Reset accelertion to 0 each cycle
    acc = 0;  
}


void Boid::draw() {
    
    // Draw a triangle rotated in the direction of velocity
	
    
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
    
	/* DRAW BOID ARROW - REPLACED WITH PNG IN FINAL VERSION
    ofBeginShape();
    ofVertex(0, -r*2);
    ofVertex(-r, r*2);
    ofVertex(r, r*2);
    ofEndShape(true);
    */
    
    // DRAW PNG IMAGE FOR AIRPLANE
    i.setAnchorPoint(10, 12);
    i.draw(0,0);
    
    ofPopMatrix();
	ofDisableAlphaBlending();
    
    
    // Draw the predicted location
    if (debug) {
		ofFill();
        
		ofSetColor(0,191,255); // BLUE
		ofLine(loc.x,loc.y,predictLoc.x, predictLoc.y);
        
        // PREDICTED LOCATION 
		ofEllipse(predictLoc.x, predictLoc.y,4,4);

		// Draw normal location
		ofSetColor(255, 69, 0); //ORANGE
		ofLine(predictLoc.x, predictLoc.y, target.x, target.y);
		ofEllipse(target.x,target.y,4,4);
		
		// Draw actual target (red if steering towards it)
		ofLine(predictLoc.x,predictLoc.y,target.x,target.y);
		

        // VIOLET CIRCLE IS TARGET + DIR
		ofSetColor(255, 20, 147);
		ofEllipse(target.x+dir.x, target.y+dir.y, 8, 8);
    }

    
}

void Boid::intersects(ofxCvContourFinder& _cv, Path* _path){

    
    ofPoint heading = loc + vel*30;  // A vector pointing from the location to where the boid is heading
    
    for ( int i = 0; i < _cv.blobs.size(); i++ ) {
        ofxCvBlob temp = _cv.blobs[i];
        ofPolyline l;
        l.addVertexes(temp.pts);
        
        if(l.inside(heading))
        {   
            counter = 0;
            avoidObject = true;
            ofPoint force = heading - _cv.blobs[i].centroid;
            ofPoint force2 = getNormalPoint(force, heading, _cv.blobs[i].centroid);
            acc += force.normalize()* 1.5;
            cout << "bounce!\n";
            
        } else {
            avoidObject = false;
            counter++;
        }
        
    }    
    
    if ( counter > 400 && avoidObject == false) {
        follow(_path);
    }

        
}

void Boid::follow(Path* p) {
    
    ofPoint predict = vel;
    Path::normalize(&predict);
    predict *= 30;
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
			dir*=5;
		}
    }
	
    // Steer if the record object is even slightly off the center of the path
    if (record > 1) {
		target += dir;
		seek(target);
        
    }
    
}
           
ofPoint Boid::getNormalPoint(ofPoint p, ofPoint a, ofPoint b) {
	
    // Vector from a to p
    ofPoint ap = p - a;
	
    // Vector from a to b
    ofPoint ab = b - a;
	
    // Normalize the line
	Path::normalize(&ab); 
	
    // Project vector "diff" onto line by using the dot product
    ab *= Path::dotproduct(ab, ap);
	
    return a + ab;
}

ofPoint Boid::steer(ofPoint target, bool slowdown) {
    // The steering vector
    ofPoint steer; 
    
    // A vector pointing from the location to the target
    ofPoint desired = target - loc;  
    
    // Distance from the target is the magnitude of the vector
    float d = ofDist(target.x, target.y, loc.x, loc.y); 
    
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


