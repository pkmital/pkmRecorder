/*
 *  pkmDiskRecorder.h
 *  dbLogger
 *
 *  Created by Mr. Magoo on 11/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "pkmEXTAudioFileReader.h"
#include "pkmEXTAudioFileWriter.h"

class pkmDiskRecorder
{
public:
	pkmDiskRecorder(string name, int fS, bool overwrite = true)
	:
	filename(name), offset(0), frameSize(fS)
	{
		if (!overwrite && reader.open(name))
		{
			offset = reader.mNumSamples;
		}
	}
	
	bool add(float *buf, int size)
	{
		writer.open(filename);
		writer.write(buf, offset, size);
		writer.close();
		offset+=size;
	}
	
private:
	int frameSize;
	int offset;
	string filename;
	pkmEXTAudioFileReader reader;
	pkmEXTAudioFileWriter writer;
};