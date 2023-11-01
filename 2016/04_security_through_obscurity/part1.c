#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LEN 64
#define CHECKSUM_LEN 5
#define bool char

struct room {
	char *name;
	int sector_id;
	char checksum[CHECKSUM_LEN + 1];
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

	// checksum
	for(j = 1; i + j < strlen(line) && j <= CHECKSUM_LEN; j++){
		room->checksum[j - 1] = line[i +j];
	}
	room->checksum[CHECKSUM_LEN] = '\0';

	return room;
}

void destroy(struct room* room){
	free(room->name);
	free(room);
}

char* generate_checksum(struct room* room){
	// create character frequency table
	int freq['z' - 'a' + 1] = { 0 };
	int i;

	for(i = 0; i < strlen(room->name); i++){
		if(room->name[i] != '-'){
			freq[room->name[i] - 'a']++;
		}
	}

	// generate checksum
	char* checksum = calloc(sizeof(char), CHECKSUM_LEN + 1);
	int j, most_frequent_character;

	for(i = 0; i < CHECKSUM_LEN; i++){
		most_frequent_character = 0;

		for(j = 1; j < 'z' - 'a' + 1; j++){
			if(freq[most_frequent_character] < freq[j]){
				most_frequent_character = j;
			}
		}

		checksum[i] = 'a' + most_frequent_character;
		freq[most_frequent_character] = 0;
	}
	checksum[CHECKSUM_LEN] = '\0';

	return checksum;
}

int main(){
	char line[MAX_INPUT_LEN], *checksum;
	struct room* room;
	int real_room_sector_id_sum = 0;

	while(scanf("%s", line) != EOF){
		room = parse_line(line);
		checksum = generate_checksum(room);
		
		if(strcmp(room->checksum, checksum) == 0){
			real_room_sector_id_sum += room->sector_id;
		}
		
		free(checksum);
		destroy(room);	
	}	

	printf("%d\n", real_room_sector_id_sum);

	return 0;
}
