all:
	gcc -O3 -Wall -Wextra bnk_pc_extractor.c -o bnk_pc_extractor.exe
	gcc -O3 -Wall -Wextra bnk_pc_packer.c -o bnk_pc_packer.exe
	gcc -O3 -Wall -Wextra hash.c -o hash.exe
	gcc -O3 -Wall -Wextra dmav_subtitles.c -o dmav_subtitles.exe
