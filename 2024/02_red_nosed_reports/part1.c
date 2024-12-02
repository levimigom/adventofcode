#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LEN 128

bool is_numeric(char c){
	return('0' <= c && c <= '9');
}

int count_levels(char *line){
	int i, line_length, levels;

	line_length = strlen(line);
	for(i = levels = 1; i < line_length; i++){
		if(is_numeric(line[i]) && !is_numeric(line[i - 1])){
			levels++;
		}
	}

	return levels;
}

int *get_levels(char *line, int *levels_count){
	*levels_count = count_levels(line);
	int *levels = calloc(sizeof(int), *levels_count);
	int i, j, level, line_length;

	line_length = strlen(line);
	for(i = j = level = 0; i < line_length; i++){
		if(is_numeric(line[i])){
			level = (level * 10) + line[i] - '0';			
		} else {
			levels[j++] = level;
			level = 0;
		}
	}
	
	return levels;
}

int my_abs(int n){
	return(n < 0 ? -n : n);
}

bool is_safe(int *levels, int levels_count){
	int i, diff;

	for(i = 1; i < levels_count; i++){
		diff = my_abs(levels[i] - levels[i - 1]);

		if(diff == 0 || 3 < diff){
			return false;
		}

		if(1 < i && (levels[i - 2] < levels[i - 1] && levels[i] < levels[i - 1])){
			return false;
		}

		if(1 < i && (levels[i - 2] > levels[i - 1] && levels[i] > levels[i - 1])){
			return false;
		}
	}

	return true;
}

int main(){
	char line[LEN];
	int i, levels_count, *levels, safe_count;

	safe_count = 0;
	while(fgets(line, LEN, stdin)){
		levels = get_levels(line, &levels_count);
	
		if(is_safe(levels, levels_count)){
			safe_count++;
		}

		free(levels);
	}

	printf("%d\n", safe_count);

	return 0;
}
