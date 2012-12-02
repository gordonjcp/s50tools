/* vim: set noexpandtab ai ts=4 sw=4 tw=0: */
/* 
	Copyright 2012 Gordon JC Pearce <gordon@gjcp.net>
	
	This file is part of s50tool.

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

void usage() {
	// show some quick help
	printf("\ns50tool\nWrite samples onto Roland S-series diskettes\n\n");
	printf("options:\n\t-b [bank]\tSelect bank (A-B, default A)\n\t-i\t\tInitialise tone parameters\n");
	printf("\t-r [note]\tSet root note of sample (default 60, middle C)\n");
	printf("\t-s [block]\tStart block for sample (0-18, default 0)\n\t-t [tone]\tTone to write (1-32, default 1)\n");
}	

int main (int argc, char **argv) {
	// parse command line, work out what we're going to do
	
	char c;
	
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

	printf("argc=%d\n", argc);

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
			case 'h': usage();
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
	
	// if we have one option remaining, it's the sample name
	// if there's two, the first is the device or image to write to
	printf("remaining: %d\n", argc-optind);
	
	    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }
	
}
