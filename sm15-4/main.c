#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char s[120]="The quick brown fox jumps over the lazy dog.";
	char *token;
	if(argc==2) {
		strcpy(s, argv[1]);
	} else {
		printf("%s \"%s\"\n", argv[0], s);
	}
	token=strtok(s," ");
	while(token!=NULL) {
		printf("%s\n",token);
		token=strtok(NULL," ");
	}
	exit(EXIT_SUCCESS);
}
