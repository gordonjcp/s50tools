/* vim: set noexpandtab ai ts=4 sw=4 tw=0: */
/* 
	Copyright 2012 Gordon JC Pearce <gordon@gjcp.net>
	
	This file is part of s50tool.

	s50tool.c contains the main command-line processing parts of the
	sample tool for Roland S-series samplers.

	s50tool is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	s50tool is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with s50tool.  If not, see <http://www.gnu.org/licenses/>.
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sndfile.h>

#include "roland.h"


void usage() {
	// show some quick help
	printf("Usage: s50tool [options] [drive or image] samplename\nWrite samples onto Roland S-series diskettes\n");
	printf("if [drive or image] is omitted, /dev/fd0 is used\n\n");
	printf("options:\n\t-b [bank]\tSelect bank (A-B, default A)\n\t-i\t\tInitialise tone parameters\n");
	printf("\t-r [note]\tSet root note of sample (default 60, middle C)\n");
	printf("\t-s [block]\tStart block for sample (0-18, default 0)\n\t-t [tone]\tTone to write (1-32, default 1)\n");
}	

char *l_basename(char *in) {
	// horrible bodgy basename() implementation
	// I couldn't get GNU basename() to work
	char *pos;
	pos = strrchr(in, '/');
	return pos?pos+1:in;
}

int main (int argc, char **argv) {
	// parse command line, work out what we're going to do
	
	char c;
	char path[256] = "/dev/fd0";		// path for device or filename
	char tonename[8];   // name of tone, derived from sample name
	FILE *disk;
	SNDFILE *wave;
	SF_INFO wave_info;

	int bl_len, fr_len;

	// parameters
	int tone = 1;
	int bank = 0;
	int start = 0;
	int truncate = 0;
	int rootkey = 0x48;
	
	char initialise=0;
	
	// arguments:
	// -b bank (default: A)
	// -i initialise tone parameters
	// -r root note (default: 60, middle C)
	// -s start block (default: 0)
	// -t tone (default: 1)
	
	// note that the tone numbers are 1-based and run from 1-32
	// on the S-50 tones are numbered 11-18, 21-28, 31-38 and 41-48

	// loop over optional arguments
	while ( (c = getopt(argc, argv, "b:hir:s:t:")) != -1) {
		switch(c) {
			case 'b':
				if (optarg == "b" || optarg == "B") bank = 1; // don't need to bother if it's A
				break;
			case 'i': initialise = 1; break;
			case 'r': rootkey = atoi(optarg); break;
			case 's': start = atoi(optarg); break;
			case 't': tone = atoi(optarg); break;
			case 'h': usage(); exit(0);
		}
	}
	
	if (start > 17 || start < 0) {
		fprintf(stderr, "start block must be between 0 and 17\n");
		exit(1);
	}
	if (tone > 32 || tone < 1) {
		fprintf(stderr, "tone must be between 1 and 32\n");
		exit(1);
	}
	
	if ((argc - optind) == 0) {
		usage();
		exit(1);
	}

	if ((argc-optind) == 1) {   // only have a sample name
		strncpy(tonename, l_basename(argv[optind]), 8);
	}
	
	if ((argc-optind) == 2) {   // have device name and sample name
		strncpy(path, argv[optind++], 256);
		strncpy(tonename, l_basename(argv[optind]), 8);
	}

	// now we can begin
	disk = fopen(path, "r+");
	if (!disk) {
		printf("Couldn't open %s: %s\n", path, "FIXME show error");
		exit(1);
	}

	wave = sf_open(argv[optind], SFM_READ, &wave_info);
	if (!wave) {
		printf("Couldn't open %s\n", argv[optind]);
		exit(1);
	}
	if (wave_info.channels > 1) {
		printf("Needs to be a mono sample\n");
		exit(1);
	}
        
	if (wave_info.frames > 221184) {
		printf("Wave will be truncated to 18 blocks");
		bl_len = 18;
		fr_len = 221184;
	} else {
		bl_len = (wave_info.frames/12288)+1;
		fr_len = wave_info.frames;
	}
	
	printf("%d\n", sizeof(toneparam_t));
	
	printf("%s %d %d\n", tonename, bl_len, fr_len);
	sf_close(wave);
	fclose(disk);
}
