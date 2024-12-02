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
	int i, previous, diff;

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

int *levels_without_level(int *levels, int levels_count, int level_to_remove){
	int *new_levels = calloc(sizeof(int), levels_count - 1);
	int i;

	for(i = 0; i < levels_count; i++){
		if(level_to_remove == i){
			continue;
		} if(i < level_to_remove){
			new_levels[i] = levels[i];
		} else {
			new_levels[i - 1] = levels[i];
		}
	}

	return new_levels;
}

int main(){
	char line[LEN];
	int i, j, levels_count, *levels, safe_count;

	safe_count = 0;
	while(fgets(line, LEN, stdin)){
		levels = get_levels(line, &levels_count);

		for(i = 0; i < levels_count; i++){
			int *new_levels = levels_without_level(levels, levels_count, i);

			if(is_safe(new_levels, levels_count - 1)){
				safe_count++;
				free(new_levels);
				break;
			}

			free(new_levels);
		}	

		free(levels);
	}

	printf("%d\n", safe_count);

	return 0;
}
