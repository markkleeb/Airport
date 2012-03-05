//
//  Boundaries.h
//  Airport
//
//  Created by Ali Sajjadi on 3/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Airport_Boundaries_cpp
#define Airport_Boundaries_cpp

class Boundaries {
    int xStart, yStart, xEnd, yEnd, width;

public:
    Boundaries(int _xStart, int _yStart, int _xEnd, int _yEnd);
    Boundaries(int _xStart, int _yStart, int _xEnd, int _yEnd, int _width);
    
    void draw();
    bool intersect();
};

#endif
