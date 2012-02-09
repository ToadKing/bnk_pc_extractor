/**
 * bnk_pc.h - common things shared across the extractor and packer.
 *
 * Copyright (c) 2011 Michael Lelli
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _BNK_PC_H
#define _BNK_PC_H

#define VERSION "1.3"

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define BNK_PC_HEADER 0x2020435042535756ULL
#define DMAV_HEADER 0x56414D44UL

#pragma pack(push,1)

// all values are little-endian

// k#: Value is predictable or can be computed, but use may not be known
// u#: Value use is unknown and cannot be predicted or computed

typedef struct
{
	u64 magic; // "VWSBPC  "
	u32 k1; // usually 0x00000000
	u32 k2; // usually 0x00010002
	u32 id; // ID, referenced in audio_banks.xtbl
	u32 k3; // pointer to the (count + 2)th entry?
		// essentially sizeof(header) + ((count + 1) * 16)
	u32 count; // number of entry items
} header;

typedef struct
{
	u32 id; // technically unknown, but most likely an ID
	u32 offset; // offset of data in the file, including 28-byte header.
		    // each file is padded with null bytes to the next offset
		    // that's a multiple of 0x800, including padding after the
		    // last file
	u32 dmav; // size of DMAV before before file, 0 if no DMAV
	u32 length; // size of file
} entry;

typedef struct
{
	u32 magic; // "DMAV"
	u32 version; // 1
	u32 persona_id; // <Persona_id> in character's voice table, voc_sb_line_sit.xtbl, and voice_dynamic_dialog_events.xtbl, <wwise_id> in audio_personas.xtbl
	u32 voiceline_id; // <Voiceline_id> in voice_control.xtbl, <wwise_id> in audio_line_tags.xtbl
	u32 offset1; // same as offset2
	u32 u1;
	u32 u2;
	u32 offset2; // same as offset1
	u32 u3;
} dmav_header;

typedef struct
{
	u32 size; // length of subtitle entry
	u32 offset; // offset from end of subtitle entry metadatas
} dmav_subtitle_header;

#pragma pack(pop)

#define is_wav(a) ((a)[0] == 'R' && (a)[1] == 'I' && (a)[2] == 'F' && (a)[3] == 'F')

#endif
