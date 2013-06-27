/*
 *  pkmRecorder.h
 *  pkmPLCA
 *  Created by Parag K Mital on 21/02/2011.
 *  Copyright 2009 Parag K Mital. All rights reserved.
 *  http://pkmital.com
 *  21/02/11
 *
 *
 *
 */

#pragma once

#include <Accelerate/Accelerate.h>


class pkmRecorder
{
public:
	pkmRecorder();
	
	~pkmRecorder();
	
	// add to end of existing buffer
	void insert(float *buf, int length);
	
	// inclusive of start, exclusive of end
	void reshape(int start, int end);
	
    void normalize(bool half = false)
    {
        if (size > 0) 
        {
            float max;
            vDSP_maxv(data, 1, &max, size);
            max = 1.0f/max;
            if(half)
                max = max/2.0f;
            vDSP_vsmul(data, 1, &max, data, 1, size);
        }
    }
    
	void reset();
	
	
	float					*data_temp;
	float					*data;
	int						size;
	
};