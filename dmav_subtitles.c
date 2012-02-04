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

#define DMAV_OFFSET 212

const char langs[11][3] = {
"us", "es", "it", "??", "de", "fr", "nl", "cz", "pl", "??", "??"
};
/*u16 char_tbl[4096] = { 0 };
u16 char_tbl_len;

int parse_table(int langnum)
{
	char name[256];
	char buffer[1024];
	FILE *o;
	u16 len = 0, i;

	sprintf(name, "charlist_%s.dat", langs[langnum / 2]);
	o = fopen(name, "r");

	if (o == NULL)
	{
		printf("cannot open %s for character data\n", name);
		return 1;
	}

	while (len == 0)
	{
		int t;
		fgets(buffer, sizeof(buffer), o);

		if (feof(o))
		{
			printf("malformed charlist file (%s)\n", name);
			fclose(o);
			return 1;
		}

		sscanf(buffer, "count=%hu\r\n", &len);
	}

	char_tbl_len = len;

	for (i = 0; i < len; i++)
	{
		fscanf(o, "%d\r\n", &char_tbl[i]);
	}

	fclose(o);

	return 0;
}*/

int main(int argc, char *argv[])
{
	FILE *f = NULL;
	FILE *o = NULL;
	dmav_header head;
	dmav_subtitle_header sub_head;
	int r = 0, count = 0, t = 0, i = 0;
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
	else if (t == 2)
	{
		fseek(f, head.offset1 + sizeof(dmav_header) + DMAV_OFFSET, SEEK_SET);
	}
	else
	{
		fseek(f, head.offset1 + sizeof(dmav_header), SEEK_SET);
	}

	fread(&sub_head, sizeof(dmav_subtitle_header), 1, f);

	sprintf(oname, "%s.html", name);
	o = fopen(oname, "w");
	fprintf(o, "<title>%s DMAV</title>\n", name);
	fprintf(o, "<pre><b>HEADER:</b>\n");
	fprintf(o, "magic:   DMAV\n");
	fprintf(o, "version:      0x%08X\n", head.version);
	fprintf(o, "persona_id:   0x%08X\n", head.persona_id);
	fprintf(o, "voiceline_id: 0x%08X\n", head.voiceline_id);
	fprintf(o, "offset1:      0x%08X\n", head.offset1);
	fprintf(o, "u1:           0x%08X\n", head.u1);
	fprintf(o, "u2:           0x%08X\n", head.u2);
	fprintf(o, "offset2:      0x%08X\n", head.offset2);
	fprintf(o, "u3:           0x%08X\n\n", head.u3);
	fprintf(o, "<b>SUBTITLE HEADER:</b>\n");
	fprintf(o, "last:   0x%08X\n", sub_head.last);
	fprintf(o, "offset: 0x%08X\n", sub_head.offset);
	fprintf(o, "u1:     0x%08X\n", sub_head.u1);
	fprintf(o, "u2:     0x%08X\n\n", sub_head.u2);

	for (i = 0; i < sizeof(langs) * 2; i++)
	{
		/*if (parse_table(i))
		{
			goto error;
		}*/

		fprintf(o, "%s: ", langs[i / 2]);

		for (;;)
		{
			u16 charcode;
			fread(&charcode, 2, 1, f);
			count += 2;

			if (charcode == 0 || feof(f))
			{
				break;
			}

			if (charcode < 0xff)
			{
				fprintf(o, "%c", charcode);
			}
			else
			{
				//fprintf(o, "&#%hu;", char_tbl[charcode - 0x100]);
				fprintf(o, "&#%hu;", charcode);
			}
		}

		if (count > sub_head.offset)
		{
			break;
		}

		fprintf(o, "\n");
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
