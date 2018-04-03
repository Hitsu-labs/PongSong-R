#include "defparser.h"
#include <stdlib.h>

char *data[4];
char *str;
int bpm;
FILE *fp;

typedef struct {
	char * data_list;
	Uint32 max_data;
}DataManager;
static DataManager data_manager;

void datainit(Uint32 max) {
	data_manager.max_data = max;
	data_manager.data_list = (char*)malloc(sizeof(char)*max);
	memset(data_manager.data_list, 0, sizeof(char)*max);
}

void fuckingwork() {
	slog("fucking working");
}
void z_file_load() {
	int i = 0;
	fp = fopen("muso.txt","r");

	if (fp == NULL) {
		slog("You're bad at opening files");
		return;
	}
	while (fgets(data[i]=malloc(200*sizeof(char)), 200, fp)!=NULL) {
		slog("%s", data[i]);
		slog("%d", i);
		i++;
		//return;
	}
	return;

}
//getters
char* getsong() {
	for (int i = 0; i < 4; i++) {
		slog("%s", data[i]);
	}
	return data[0];
}

char* getpaddle() {
	return data[1];
}

char* getball() {
	return data[2];
}

int getbpm() {
	bpm = atoi(data[3]);
	return bpm;
}
