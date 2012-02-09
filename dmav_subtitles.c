/**
 * dmav_subtitles.c - parse subtitle data in DMAV sections of voice clips
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
#include "char_tbl_latin.h"
#include "char_tbl_jp.h"
#include "char_tbl_sk.h"

const char langs[14][3] = {
"us",
"es",
"it",
"jp",
"de",
"fr",
"nl",
"??",
"??",
"cz",
"pl",
"sk",
"ru",
"??"
};

const u16 *lang_tables[14] = {
char_tbl_latin,
char_tbl_latin,
char_tbl_latin,
char_tbl_jp,
char_tbl_latin,
char_tbl_latin,
char_tbl_latin,
0,
0,
char_tbl_latin,
char_tbl_latin,
char_tbl_sk,
char_tbl_latin,
0
};

int main(int argc, char *argv[])
{
	FILE *f = NULL;
	FILE *o = NULL;
	dmav_header head;
	dmav_subtitle_header sub_head[28];
	int r = 0, t = 0, i = 0, offset = sizeof(sub_head) + 4;
	char name[1024];
	char oname[1024];

	if (argc != 2)
	{
		printf("dmav_subtitles " VERSION "\n"
		       "usage: %s voicedata.dmav\n", argv[0]);
		goto error;
	}

	memcpy(name, argv[1], strlen(argv[1]) + 1);
	name[strrchr(name, '.') - name] = 0;

	f = fopen(argv[1], "rb");

	if (f == NULL)
	{
		printf("cannot open file\n");
		goto error;
	}

	fread(&head, sizeof(dmav_header), 1, f);

	if (head.magic != DMAV_HEADER)
	{
		printf("not a dmav file\n");
		goto error;
	}

	if (head.offset1 != head.offset2)
	{
		printf("WARNING: offsets not equal, results might not be correct\n");
	}

	fseek(f, head.offset1 + sizeof(dmav_header), SEEK_SET);
	fread(&t, 4, 1, f);

	if (t == 0)
	{
		printf("file has no subtitle data\n");
		goto end;
	}

	sprintf(oname, "%s.html", name);
	o = fopen(oname, "w");
	fprintf(o, "<title>%s DMAV</title>\n", name);
	fprintf(o, "<pre><b>HEADER:</b>\n");
	fprintf(o, "magic:        \"DMAV\"\n");
	fprintf(o, "version:      0x%08X\n", head.version);
	fprintf(o, "persona_id:   0x%08X\n", head.persona_id);
	fprintf(o, "voiceline_id: 0x%08X\n", head.voiceline_id);
	fprintf(o, "offset1:      0x%08X\n", head.offset1);
	fprintf(o, "u1:           0x%08X\n", head.u1);
	fprintf(o, "u2:           0x%08X\n", head.u2);
	fprintf(o, "offset2:      0x%08X\n", head.offset2);
	fprintf(o, "u3:           0x%08X\n\n", head.u3);
	fprintf(o, "<b>SUBTITLE HEADERS:</b>\n\n");

	if (t != 2)
	{
		fseek(f, head.offset1 + sizeof(dmav_header), SEEK_SET);
		offset = sizeof(dmav_subtitle_header) * 2;
	}

	// loop 1: get subtitle headers
	for (i = 0; i < sizeof(sub_head) / sizeof(*sub_head); i++)
	{
		if (offset == sizeof(dmav_subtitle_header) * 2 && i > 1)
		{
			break;
		}

		fread(&sub_head[i], sizeof(dmav_subtitle_header), 1, f);
	}

	// loop 2: output headers + get subtitles
	for (i = 0; i < sizeof(sub_head) / sizeof(*sub_head); i++)
	{
		int l = i % 14;
		int count = 0;

		if (offset == sizeof(dmav_subtitle_header) * 2 && i > 1)
		{
			break;
		}

		fprintf(o, "size: 0x%08X\n", sub_head[i].size);
		fprintf(o, "offset: 0x%08X\n", sub_head[i].offset);
		fprintf(o, "%s: ", langs[l]);

		fseek(f, head.offset1 + sizeof(dmav_header) + offset + sub_head[i].offset, SEEK_SET);

		while (count + 2 < sub_head[i].size)
		{
			u16 charcode;

			fread(&charcode, 2, 1, f);
			count += 2;
			charcode = lang_tables[l][charcode];

			if (charcode < 0xff && !!charcode)
			{
				fprintf(o, "%c", charcode);
			}
			else
			{
				fprintf(o, "&#%hu;", charcode);
			}
		}

		fprintf(o, "\n\n");
	}
end:

	if (f != NULL)
	{
		fclose(f);
	}

	if (o != NULL)
	{
		fprintf(o, "</pre>\n");
		fclose(o);
	}

	return r;

error:
	r = 1;
	goto end;
}
