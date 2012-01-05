all:
	gcc -O3 bnk_pc_extractor.c -o bnk_pc_extractor.exe
	gcc -O3 bnk_pc_packer.c -o bnk_pc_packer.exe
	gcc -O3 hash.c -o hash.exe
