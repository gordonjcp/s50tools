/* vim: set noexpandtab ai ts=4 sw=4 tw=0: */
/* 
	Copyright 2012 Gordon JC Pearce <gordon@gjcp.net>
	
	This file is part of s50tool.

	roland.c contains the functions for processing a sound file into
	a format recognisable by Roland S-series samplers.

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

static void pack_block(short *w_in, char *out) {
	// turn a block of 12288 samples into 18432 bytes
	int i, j;
	short s1, s2;

	for(i=0, j=0; i<=12288; i+=2, j+=3) {
		s1 = w_in[i]; s2 = w_in[i + 1];
		out[j]=s1>>8;
		out[j+1]=(s1 & 0x00f0) | (s2 & 0x00f0)>>4;
		out[j+2]=s2>>8;
	}
}


