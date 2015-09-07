#include <string.h>

char *getParam(int argc, char *argv[]){
	char *name = "PLAYER";

	if (argc > 1){
		if (strncmp(argv[1], "-p", 2) == 0) {
			if (strlen(argv[1]) > 2)  name = (argv[1] + 2);
			else  if (2 < argc) //spr czy nie wyjdzie poza zakres tablicy
				name = argv[2];
		};
	};
	return name;
}