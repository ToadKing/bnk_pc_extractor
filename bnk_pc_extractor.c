/**
 * bnk_pc_extractor.c - a simple extractor of .bnk_pc files found in Saints
 * Row: The Third. Also a crude documentation of discoveries about the
 * archive format.
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

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <direct.h>

#define is_wav(a) ((a)[0] == 'R' && (a)[1] == 'I' && (a)[2] == 'F' && (a)[3] == 'F')

typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

#pragma pack(push,1)

// all values are little-endian

// k#: Value is predictable or can be computed, but use may not be known
// u#: Value use is unknown and cannot be predicted or computed

struct _header
{
	u64 magic; // "VWSBPC  "
	u32 k1; // usually 0x00000000
	u32 k2; // usually 0x00010002
	u32 u1; // unknown; maybe an ID?
	u32 k3; // pointer to the (count + 2)th entry?
		// essentially sizeof(header) + ((count + 1) * 16)
	u32 count; // number of entry items
};

struct _entry
{
	u32 u1; // unknown; seems to increase with each entry, maybe an ID?
	u64 offset; // offset of data in the file, including 28-byte header.
		    // each file is padded with null bytes to the next offset
		    // that's a multiple of 0x800, including padding after the
		    // last file
	u32 length; // file length
};

#pragma pack(pop)

typedef struct _header header;
typedef struct _entry entry;

int main(int argc, char *argv[])
{
	FILE *f = NULL;
	FILE *out = NULL;
	u32 i;
	header head;
	entry *entries = NULL;
	char *name = NULL;
	char *filename = NULL;
	int r = 0;

	if (argc > 2)
	{
		f = fopen(argv[1], "rb");

		if (f == NULL)
		{
			printf("file can't be opened\n");
			goto error;
		}

		out = fopen(argv[2], "w");

		if (out == NULL)
		{
			printf("log can't be opened for writin\n");
			goto error;
		}
	}
	else if (argc > 1)
	{
		f = fopen(argv[1], "rb");

		if (f == NULL)
		{
			printf("file can't be opened\n");
			goto error;
		}

		out = stdout;
	}
	else
	{
		printf("usage: %s file.bnk_pc [log.txt]\n(files are not dumped if log is enabled)\n", argv[0]);
		goto error;
	}

	name = malloc(strlen(argv[1]) + 1);
	filename = malloc(strlen(argv[1]) + 10);
	memcpy(name, argv[1], strlen(argv[1]) + 1);
	name[strrchr(name, '.') - name] = 0;
	fread(&head, sizeof(header), 1, f);

	if (head.magic != 0x2020435042535756ULL /* "VWSBPC  " */)
	{
		if (head.magic == 0x0000001844484B42ULL /* "BHKD\x18\x00\x00\x00" */)
			printf("file incorrect format, try %s_media.bnk_pc instead\n", name);
		else
			printf("file incorrect format");
		goto error;
	}
	
	fprintf(out, "HEADER\n");
	fprintf(out, "magic:  \"VWSBPC  \"\n");
	fprintf(out, "k1:     0x%08X\n", head.k1);
	fprintf(out, "k2:     0x%08X\n", head.k2);
	fprintf(out, "u1:     0x%08X\n", head.u1);
	fprintf(out, "k3:     0x%08X\n", head.k3);
	fprintf(out, "count:  0x%08X\n", head.count);

	entries = malloc(sizeof(entry) * head.count);;

	for(i = 0; i < head.count; i++)
	{
		entry e = entries[i];

		if (fread(&e, sizeof(entry), 1, f) != 1)
		{
			break;
		}

		fprintf(out, "\n%05u:\n", i);
		fprintf(out, "u1:     0x%08X\n", e.u1);
		fprintf(out, "offset: 0x%016llX\n", e.offset);
		fprintf(out, "length: 0x%08X\n", e.length);

		if (argc == 2)
		{
			int currPos = ftell(f);
			u8 *buffer = malloc(e.length);
			FILE *sav;
			fseek(f, e.offset, SEEK_SET);
			fread(buffer, e.length, 1, f);
			fseek(f, currPos, SEEK_SET);

			sprintf(filename, "%s_%05u.%s", name, i, is_wav(buffer) ? "wav" : "bin");
			sav = fopen(filename, "wb");
			fwrite(buffer, e.length, 1, sav);
			fclose(sav);
			free(buffer);
		}
	}

end:
	free(name);
	free(filename);
	free(entries);

	if (f != NULL)
	{
		fclose(f);
	}

	if (out != NULL && out != stdout)
	{
		fclose(out);
	}

	return r;

error:
	r = 1;
	goto end;
}
