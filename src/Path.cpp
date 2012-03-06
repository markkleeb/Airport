//
//  Path.cpp
//  Airport
//
//  Created by Mark Kleback on 3/5/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#include <iostream>
#include "Path.h"

Path::Path() {
    
    radius = 20;
    
    
}

void Path::addPoint(float x, float y) {
    ofPoint point;
    point.set(x, y);
    points.push_back(point);
    
}

void Path::draw() {
    
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(255, 255, 255);
    ofBeginShape();
    
    for(int i = 0; i < points.size(); i++){
        
        ofVertex(points[i].x, points[i].y);
    }
    
    ofEndShape();
    
}
