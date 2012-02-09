#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned int hashFnv(char *input)
{
	unsigned int hash = 0x811C9DC5;
	unsigned int i;

	for (i = 0; i < strlen(input); i++)
	{
		unsigned int c = input[i];

		if (c == ':')
		{
			// for us, we reset the hash function at a colon
			hash = 0x811C9DC5;
			continue;
		}

		if ((c - 0x41) <= 0x19)
		{
			c += 0x20;
		}

		hash *= 0x1000193;
		hash ^= c;
	}

	return hash;
}

unsigned int hashVol(char *input)
{
	unsigned int hash = 0;
	unsigned int i;

	for (i = 0; i < strlen(input); i++)
	{
		unsigned int c = input[i];

		if (c == ':')
		{
			hash = 0;
			continue;
		}

		if ((c - 0x41) <= 0x19)
		{
			c += 0x20;
		}

		// rotate left by 6
		hash = (hash << 6) | (hash >> (32 - 6));
		hash = c ^ hash;
	}

	return hash;
}

#define MOD_ADLER 65521

unsigned int hashAdl(char *input)
{
	unsigned int a = 1, b = 0;
	unsigned int i;

	for (i = 0; i < strlen(input); ++i)
	{
		unsigned int c = input[i];

		if (c == ':')
		{
			a = 1;
			b = 0;
			continue;
		}

		if ((c - 0x41) <= 0x19)
		{
			c += 0x20;
		}

		a = (a + c) % MOD_ADLER;
		b = (b + a) % MOD_ADLER;
	}

	return (b << 16) | a;
}

int main(int argc, char *argv[])
{
	unsigned int fnv, vol, adl;

	if (argc != 2)
	{
		return 1;
	}

	fnv = hashFnv(argv[1]);
	vol = hashVol(argv[1]);
	adl = hashAdl(argv[1]);

	printf("%s:\nfnv: %u (0x%08X)\nvol: %u (0x%08X)\nadl: %u (0x%08X)\n", argv[1], fnv, fnv, vol, vol, adl, adl);

	return 0;
}
