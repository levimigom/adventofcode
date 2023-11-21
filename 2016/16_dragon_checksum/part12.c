#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 64

char* generate_data(char* initial_state, int target_length){
	char *data = calloc(sizeof(char), target_length);
	int i, length, current_length;
	
	for(i = 0; i < strlen(initial_state); i++){
		data[i] = initial_state[i];	
	}
	
	length = strlen(initial_state);
	while(length < target_length){
		current_length = length;

		data[length++] = '0';
		for(i = 0; i < current_length && length < target_length; i++){
			if(data[current_length - i - 1] == '0'){
				data[length++] = '1';
			} else {
				data[length++] = '0';
			}
		}
	}	

	return data;
}

char* calculate_checksum(char *data, int length){
	char* checksum = calloc(sizeof(char), length / 2);
	int i;
	
	for(i = 0; i < length; i += 2){
		if(data[i] == data[i + 1]){
			checksum[i / 2] = '1';
		} else {
			checksum[i / 2] = '0';
		}
	}

	return checksum;
}

int main(){
	char initial_state[MAX_LEN];
	int target_length;

	scanf("%s %d", initial_state, &target_length);

	char *data = generate_data(initial_state, target_length);
	char *checksum = calculate_checksum(data, target_length);
	int i, checksum_length = target_length / 2;

	while(checksum_length % 2 == 0){
		char *new_checksum = calculate_checksum(checksum, checksum_length);
		checksum_length /= 2;
			
		free(checksum);
		checksum = new_checksum;
	}
	
	for(i = 0; i < checksum_length; i++){
		printf("%c", checksum[i]);
	}
	printf("\n");
	
	free(checksum);
	free(data);

	return 0;
}
