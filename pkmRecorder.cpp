/*
 *  pkmRecorder.cpp
 *  pkmPLCA
 *  Created by Parag K Mital on 21/02/2011.
 *  Copyright 2009 Parag K Mital. All rights reserved.
 *  http://pkmital.com
 *  21/02/11
 *
 *
 *  Performs foreground/background separation of signals
 *
 *  Dependencies on OpenCV 2.1+ and ofxMaxim
 *
 *
 *  2d plca based on matlab code by Paris Smaragdis, <paris@media.mit.edu>,
 *  with additional code on Lambert's W(z) and iterations based on code from Madhu Shashanka, <shashanka@cns.bu.edu>
 * 
 *  Labert's W iterations
 %  fixed-point iterations of eqns 14 and 19 in [1]
 %  [1] Brand, M. "Pattern Discovery via Entropy Minimization"
 %  01 Aug 2006
 *
 %  Eq (38) and Eq (39), page 23 from
 %  Brand, M. "Structure learning in Conditional Probability
 %  Models via an entropic prior and parameter extinction", 1998.
 %  Available at: http://www.merl.com/reports/docs/TR98-18.pdf
 *
 *
 */

#include "pkmRecorder.h"
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <Accelerate/Accelerate.h>

pkmRecorder::pkmRecorder()
{
	data_temp = NULL;
	data = NULL;
	size = 0;
}

pkmRecorder::~pkmRecorder()
{
	reset();
}

void pkmRecorder::insert(float *buf, int length)
{
	if (length > 0) 
	{
		if (size > 0) 
		{
			// resize
			int newSize = length + size;
			data_temp = (float *)malloc(sizeof(float)*newSize);
			
			// copy existing float buffer
			cblas_scopy(size, data, 1, data_temp, 1);
			
			// copy new float buffer
			cblas_scopy(length, buf, 1, data_temp+size, 1);
			
			// clean up old array
			//delete [] data;
			
			// keep variables
			std::swap(data,data_temp);
			free(data_temp);
			size = newSize;
		}
		else {
			data = (float *)malloc(sizeof(float)*length);
			memcpy(data, buf, sizeof(float)*length);
			size = length;
		}
	}
}

void pkmRecorder::reshape(int start, int end)
{
	if (end > start && end <= size) {
		int newSize = end - start;
		
		data_temp = (float *)malloc(sizeof(float)*newSize);
		cblas_scopy(newSize, data+start, 1, data_temp, 1);
		//memcpy(data_temp, data+start, sizeof(float)*newSize);
		
		free(data);
		
		std::swap(data,data_temp);
		size = newSize;
		
	}
}

void pkmRecorder::reset()
{
	size = 0;
	free(data);
}