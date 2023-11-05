#include <stdio.h>
#include <string.h>
#define LEN 20000

int calculate_decompressed_length(char *sequence){
	int i, length, characters, repeat;

	length = 0;
	for(i = 0; i < strlen(sequence); i++){
		if('A' <= sequence[i] && sequence[i] <= 'Z'){
			length++;
		} else {
			i++;

			characters = 0;
			while(sequence[i] != 'x'){
				characters = (10 * characters) + (sequence[i] - '0');
				i++;
			}
			i++;

			repeat = 0;
			while(sequence[i] != ')'){
				repeat = (10 * repeat) + (sequence[i] - '0');
				i++;
			}

			length += characters * repeat;
			i += characters;
		}
	}

	return length;
}

int main(){
	char sequence[LEN];

	scanf("%s", sequence);
	printf("%d\n", calculate_decompressed_length(sequence));

	return 0;
}
