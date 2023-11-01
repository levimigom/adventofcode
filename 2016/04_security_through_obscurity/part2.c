#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LEN 64
#define bool char
#define SEARCH_STRING "northpole object storage "

struct room {
	char *name;
	int sector_id;
};

bool is_digit(char c){
	return '0' <= c && c <= '9';
}

struct room* parse_line(char* line){
	struct room* room = malloc(sizeof(struct room));
	int i, j;
	
	// name
	i = 0;
	while(i < strlen(line) && !is_digit(line[i])) i++;
	
	room->name = calloc(sizeof(char), i + 1);
	for(j = 0; j < i; j++){
		room->name[j] = line[j];
	}
	room->name[i] = '\0';

	// sector id
	room->sector_id = 0;
	for(; i < strlen(line) && is_digit(line[i]); i++){
		room->sector_id = (room->sector_id * 10) + (line[i] - '0');
	}

	return room;
}

void destroy(struct room* room){
	free(room->name);
	free(room);
}

char* decipher_name(struct room* room){
	char* name = calloc(sizeof(char), strlen(room->name) + 1);
	int i;

	for(i = 0; i < strlen(room->name); i++){
		if(room->name[i] == '-'){
			name[i] = ' ';
		} else {
			name[i] = 'a' + (room->name[i] - 'a' + room->sector_id) % ('z' - 'a' + 1);
		}
	}
	name[i] = '\0';

	return name;
}

int main(){
	char line[MAX_INPUT_LEN], *deciphered_name;
	struct room* room;

	while(scanf("%s", line) != EOF){
		room = parse_line(line);
		deciphered_name = decipher_name(room);
		
		if(strcmp(deciphered_name, SEARCH_STRING) == 0){
			printf("The room '%s' is located in sector %d\n", SEARCH_STRING, room->sector_id);
		}

		free(deciphered_name);
		destroy(room);	
	}	

	return 0;
}
