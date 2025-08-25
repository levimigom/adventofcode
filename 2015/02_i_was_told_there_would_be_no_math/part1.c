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

int area(int l, int w, int h){
	return 2 * (l * w + w * h + h * l);
}

int calculate_wrapping_paper(int l, int w, int h){
	return area(l, w, h) + min(l * w, min(w * h, l * h));
}

int main(){
	char s[32];
	int *arr, total_wrapping_paper;
	
	arr = calloc(sizeof(int), 3);
	total_wrapping_paper = 0;
	while(scanf("%s", s) != EOF){
		parse(s, 'x', &arr);	

		total_wrapping_paper += calculate_wrapping_paper(arr[0], arr[1], arr[2]);
	}
	
	printf("%d\n", total_wrapping_paper);
	free(arr);

	return 0;
}
