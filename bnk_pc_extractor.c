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

#include "bnk_pc.h"

int main(int argc, char *argv[])
{
	FILE *f = NULL;
	FILE *out = NULL;
	u32 i;
	header head;
	entry *entries = NULL;
	char name[1024];
	int r = 0;

	if (argc > 3 || argc < 2)
	{
		printf("bnk_pc_extractor " VERSION "\n"
		       "usage: %s file.bnk_pc [log.txt]\n"
		       "files are dumped to the .bnk_pc file's directory\n"
		       "log is dumped to <filename>.txt if no log file specified\n", argv[0]);
		goto error;
	}

	memcpy(name, argv[1], strlen(argv[1]) + 1);
	name[strrchr(name, '.') - name] = 0;

	f = fopen(argv[1], "rb");

	if (f == NULL)
	{
		printf("file %s can't be opened\n", argv[1]);
		goto error;
	}

	if (argc == 2)
	{
		char logname[1024];
		sprintf(logname, "%s.txt", name);
		out = fopen(logname, "w");
	}
	else
	{
		out = fopen(argv[2], "w");
	}

	if (out == NULL)
	{
		printf("log %s can't be opened for writing\n", argv[2]);
		goto error;
	}

	fread(&head, sizeof(header), 1, f);

	if (head.magic != 0x2020435042535756ULL /* "VWSBPC  " */)
	{
		if (head.magic == 0x0000001844484B42ULL /* "BHKD\x18\x00\x00\x00" */)
			printf("file incorrect format, try %s_media.bnk_pc instead\n", name);
		else
			printf("file incorrect format");
		goto error;
	}

	fprintf(out, "ONLY EDIT THE FILENAMES\n");
	fprintf(out, "HEADER:\n");
	fprintf(out, "magic:  \"VWSBPC  \"\n");
	fprintf(out, "k1:     0x%08X\n", head.k1);
	fprintf(out, "k2:     0x%08X\n", head.k2);
	fprintf(out, "id:     0x%08X\n", head.id);
	fprintf(out, "k3:     0x%08X\n", head.k3);
	fprintf(out, "count:  0x%08X\n", head.count);

	entries = calloc(head.count, sizeof(entry));

	for(i = 0; i < head.count; i++)
	{
		int currPos;
		u8 *buffer;
		char filename[1024];
		FILE *sav;

		if (fread(&(entries[i]), sizeof(entry), 1, f) != 1)
		{
			printf("unexpected end of file\n");
			goto error;
		}

		buffer = malloc(entries[i].length + entries[i].dmav);

		currPos = ftell(f);
		fseek(f, entries[i].offset, SEEK_SET);
		fread(buffer, entries[i].length + entries[i].dmav, 1, f);
		fseek(f, currPos, SEEK_SET);

		if (entries[i].dmav != 0)
		{
			sprintf(filename, "%s_%05u.dmav", name, i);
			sav = fopen(filename, "wb");
			fwrite(buffer, entries[i].dmav, 1, sav);
			fclose(sav);
		}

		sprintf(filename, "%s_%05u.%s", name, i, is_wav(&(buffer[entries[i].dmav])) ? "wav" : "bin");
		sav = fopen(filename, "wb");
		fwrite(&(buffer[entries[i].dmav]), entries[i].length, 1, sav);
		fclose(sav);

		free(buffer);
		fprintf(out, "\n%05u:  %s\n", i, filename);
		fprintf(out, "id:     0x%08X\n", entries[i].id);
		fprintf(out, "offset: 0x%08X\n", entries[i].offset);
		fprintf(out, "dmav:   0x%08X\n", entries[i].dmav);
		fprintf(out, "length: 0x%08X\n", entries[i].length);
	}

end:
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
