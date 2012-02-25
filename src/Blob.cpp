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