/* vim: set noexpandtab ai ts=4 sw=4 tw=0: */
/* 
	Copyright 2012 Gordon JC Pearce <gordon@gjcp.net>
	
	This file is part of s50tool.

	roland.h contains various definitions used by roland.c, in particular
	the structs used on Roland S-series disks

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
	
#ifndef __ROLAND_H
#define __ROLAND_H

// some information on structs gained from
// http://www.youngmonkey.ca/nose/audio_tech/synth/Roland-S_DiskFormat.html
// and
// http://www.milton.arachsys.com/nj71/index.php?menu=2&submenu=4&subsubmenu=2&page=5

// offsets in bytes
#define PATCH_OFFSET	0x0fc00
#define TONE_OFFSET		0x10e00
#define TONEDIR_OFFSET  0x11e00
#define SAMPLE_OFFSET   0x12000

// tone directory entries
typedef struct {
	unsigned char name[8];
	unsigned char output;
	unsigned char subtone; // parent tone
	unsigned char subtone_flag; // 1 if subtone
	unsigned char rate_flag; // 1 if 15kHz
	unsigned char orig_key; // MIDI note number
	unsigned char ram_bank; // 0=A, 1=B, 2=unused tone
	unsigned char start;	// first block in RAM
	unsigned char length;   // number of blocks
} tonedir_t;

#endif
