//
//  Blob.cpp
//  Airport
//
//  Created by Mark Kleback on 2/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#include <iostream>
#include "Blob.h"
#include "ofxCvBlob.h"


Blob::Blob(vector<ofPoint> p) {
    
  //  loc.x  = 0;
  //  loc.y = 0;
    r = 20;
    points = p;
    
    
    
    
}

void Blob::update(){
    
    
}

void Blob::draw(){
    
    ofPushMatrix();
    //ofTranslate(loc.x, loc.y);
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofBeginShape();
    for(int i; i < points.size(); i ++){
        
        ofVertex(points[i].x, points[i].y);
        
        cout << "x " << points[i].x << " y " << points[i].y;
        
    }
    ofEndShape();
    ofPopMatrix();
    
    
    
}