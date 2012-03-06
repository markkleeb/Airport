//
//  Path.h
//  Airport
//
//  Created by Mark Kleback on 3/5/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#ifndef Airport_Path_h
#define Airport_Path_h

#include "ofMain.h"

class Path {
public:
	Path();
	
	void draw();
    void addPoint(float _x, float _y);
    
    vector<ofPoint> points;
    float radius;


    
};
#endif
