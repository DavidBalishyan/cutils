#include <stdio.h>
#include "clibx.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage %s <file-path>\n", argv[0]);
		return 1;
	}
	 char *filename = argv[1];
	 FILE *fp = fopen(filename, "r");
	 if (fp == NULL) ERROR("File reading error");
	 while (clibx_true) {
	   int c = fgetc(fp);
		 if (c == EOF) break;
		 printf("%c", c);
	 }
	 printf("\n");
	 fclose(fp);
   return 0;
}
