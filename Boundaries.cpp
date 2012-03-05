//
//  Boundaries.cpp
//  Airport
//
//  Created by Ali Sajjadi on 3/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Boundaries.h"
#include "ofMain.h"

Boundaries::Boundaries(int _xStart, int _yStart, int _xEnd, int _yEnd) {
    xStart = _xStart;
    yStart = _yStart;
    xEnd = _xEnd;
    yEnd = _yEnd;
    width = 6;
}

Boundaries::Boundaries(int _xStart, int _yStart, int _xEnd, int _yEnd, int _width) {
    xStart = _xStart;
    yStart = _yStart;
    xEnd = _xEnd;
    yEnd = _yEnd;
    width = _width;
    
}

void Boundaries::draw() {
    ofLine(xStart, yStart, xEnd, yEnd);
}

bool Boundaries::intersect() {
    return true;
}