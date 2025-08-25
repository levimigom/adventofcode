/**
 *	author: levimigom
 *	created: 2025-08-25 17:48:23
 **/
#include <stdio.h>
#include <stdlib.h>

int strtoi(char *s, char *e){
	int n;

	for(n = 0; *s != *e; s++){
		n = (10 * n) + *s - '0';
	}
	
	return n;
}

void parse(char *s, char delim, int **data){
	int i, j, k;

	for(i = j = k = 0; s[i]; i++){
		if(s[i] != delim){
			continue;
		}
		(*data)[k++] = strtoi(s + j, s + i);
		j = i + 1;
	}
	(*data)[k++] = strtoi(s + j, s + i);
}

int min(int a, int b){ return(a < b ? a : b); }

int volume(int l, int w, int h){
	return l * w * h;
}

int calculate_ribbon(int l, int w, int h){
	return volume(l, w, h) + 2 * min(l + w, min(w + h, l + h));
}

int main(){
	char s[32];
	int *arr, total_ribbon;
	
	arr = calloc(sizeof(int), 3);
	total_ribbon = 0;
	while(scanf("%s", s) != EOF){
		parse(s, 'x', &arr);
		total_ribbon += calculate_ribbon(arr[0], arr[1], arr[2]);
	}
	
	printf("%d\n", total_ribbon);
	free(arr);

	return 0;
}
