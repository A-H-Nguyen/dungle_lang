#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define wordnum		8
#define wordsize	6
#define NumRegs		128

bool check_dung(char *dung) {
	char dungle[wordsize + 1] = "Dungle";
	for (int i = 0; i < wordsize; i++) {
		if (i == 1) {
			if(dung[i] != 'o' && dung[i] != 'i')
				return false;
			else
				continue;
		}
		if (dung[i] != dungle[i]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Expected 1 arg: input .dung file\n");
		return 1;
	}

	short *DungleData = (short*)malloc(sizeof(short) * wordnum-1);

	FILE *fileptr = fopen(argv[1], "r");

	int linenum = 0;
	int linelen = (wordnum * wordsize);

	char *lnbuf = (char*)malloc(linelen);
	char *dung  = (char*)malloc(wordsize);

	short regval = 0x0000;

	// the magic '+2' in fgets() captures endline char in line buffer
	while (fgets(lnbuf, linelen+2, fileptr) != NULL) {
		printf("%d:\t", linenum);
		for (int i = 0; i < linelen; i += wordsize) {
			memcpy(dung, lnbuf + i, wordsize);
			
			if (check_dung(dung)) {
				if (dung[1] == 'o') {
					regval |= (0x0001 << (i/wordsize));
					printf("1");
				}
				else    printf("0");
			}
			else {
				printf("Line %d, word %d, invalid word: %s\n",
					linenum, (i/wordsize), dung);
				return 1;
			}
		}
		DungleData[linenum] = regval;
		regval = 0;

		printf("\t// %x\n", DungleData[linenum]);
		linenum++;
	}
	fclose(fileptr);
	return 0;
}
