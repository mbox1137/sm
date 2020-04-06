//https://unixhow.com/3169/chto-takoe-i-dlya-chego-nuzhen-sistemnyj-vyzov-mmap
//....
//Такой метод имеет ограничения на системах с 32-разрядным ядром, поскольку 
//там существует ограничение на максимальный размер файла, который "можно 
//отобразить". Этот предел - 4 гигабайта.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leb128.h"

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
