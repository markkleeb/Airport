//
//  Blob.cpp
//  Airport
//
//  Created by Mark Kleback on 2/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#include <iostream>
#include "Blob.h"


Blob::Blob() {
    
    loc.x  = ofRandom(ofGetWindowWidth());
    loc.y = ofRandom(ofGetWindowHeight());
    r = 20;
    
   
    
    
}

void Blob::update(){
    
    
}

void Blob::draw(){
    
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    ofSetColor(255, 0, 0);
    ofFill();
    ofCircle(0, 0, r);
    ofPopMatrix();
    
    
    
}

ofPoint Blob::dist(float _x, float _y) {
    ofPoint shortestPoint = (1000, 1000, 1000.0);
    for (int i=0; i<360; i++) {
        float angle = ofDegToRad(i);
        
        float circY = sin(angle) * r;
        float circX = cos(angle) * r;
        float dist = ofDist(_x, _y, circX, circY);
        if (dist < shortestPoint.z) {
            shortestPoint.x = circX;
            shortestPoint.y = circY;
            shortestPoint.z = dist;
        }
    }
    return shortestPoint;
}