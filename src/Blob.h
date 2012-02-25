//
//  Blob.h
//  Airport
//
//  Created by Mark Kleback on 2/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#ifndef Airport_Blob_h
#define Airport_Blob_h


#include "ofMain.h"

class Blob {
public:
	Blob();
	
	void update();
	void draw();
	ofPoint loc;
	float r;
};



#endif
