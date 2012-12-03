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

// offsets in unsigned chars
#define PATCH_OFFSET	0x0fc00
#define TONE_OFFSET		0x10e00
#define TONEDIR_OFFSET  0x11e00
#define SAMPLE_OFFSET   0x12000

// "Default" envelope, like a blank tone
unsigned char envelope[] = { 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x7f };



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

typedef struct {
	unsigned char	EnvSustainPoint;
	unsigned char	EnvEndPoint;
 	unsigned char	EnvLevel1;
	unsigned char	EnvRate1;
	unsigned char	EnvLevel2;
	unsigned char	EnvRate2;
	unsigned char	EnvLevel3;
	unsigned char	EnvRate3;
	unsigned char	EnvLevel4;
	unsigned char	EnvRate4;
	unsigned char	EnvLevel5;
	unsigned char	EnvRate5;
	unsigned char	EnvLevel6;
	unsigned char	EnvRate6;
	unsigned char	EnvLevel7;
	unsigned char	EnvRate7;
	unsigned char	EnvLevel8;
	unsigned char	EnvRate8;
} envelope_t;

typedef struct {
	unsigned char	toneName[8];
	unsigned char	outputAssign;
	unsigned char	sourceTone;
	unsigned char	orgSubTone;
	unsigned char	samplingFrequency;
	unsigned char	origKeyNumber;
	unsigned char	waveBank;
	unsigned char	waveSegmentTop;
	unsigned char	waveSegmentLength;
	unsigned char	startPoint[3];
	unsigned char	endPoint[3];
	unsigned char	loopPoint[3];
	unsigned char	loopMode;
	unsigned char	tvaLfoDepth;
	unsigned char	unknown1[1];
	unsigned char	lfoRate;
	unsigned char	lfoSync;
	unsigned char	lfoDelay;
	unsigned char	unknown2[1];
	unsigned char	lfoMode;
	unsigned char	oscLfoDepth;
	unsigned char	lfoPolarity;
	unsigned char	lfoOffset;
	unsigned char	transpose;
	unsigned char	fineTune;
	unsigned char	tvfCutOff;
	unsigned char	tvfResonance;
	unsigned char	tvfKeyFollow;
	unsigned char	unknown3[1];
	unsigned char	tvfLfoDepth;
	unsigned char	tvfEgDepth;
	unsigned char	tvfEgPolarity;
	unsigned char	tvfLevelCurve;
	unsigned char	tvfKeyRateFollow;
	unsigned char	tvfVelocityRateFollow;
	unsigned char	unknown4[1];
	unsigned char	tvfSwitch;
	unsigned char	benderSwitch;
	envelope_t tvaEnv;
	unsigned char	unknown5[1];
	unsigned char	tvaEnvKeyRate;
	unsigned char	level;
	unsigned char	envVelRate;
	unsigned char	recThreshold;
	unsigned char	recPreTrigger;
	unsigned char	recSamplingFrequency;
	unsigned char	recStartPoint[3];
	unsigned char	recEndPoint[3];
	unsigned char	recLoopPoint[3];
	unsigned char	zoomT;
	unsigned char	zoomL;
	unsigned char	copySource;
	unsigned char	loopTune;
	unsigned char	tvaLevelCurve;
	unsigned char	unknown6[12];
	unsigned char	loopLength[3];
	unsigned char	pitchFollow;
	unsigned char	envZoom;
	envelope_t tvfEnv;
	unsigned char	afterTouchSwitch;
	unsigned char	unknown7[2];
} toneparam_t;

#endif
