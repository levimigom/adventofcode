/**
 *	author: levimigom
 *	created: 2025-12-05 12:02:03
 **/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long long **read_ranges(int range_count){
	int i;	
	long long **ranges = calloc(sizeof(long long*), range_count);

	for(i = 0; i < range_count; i++){
		ranges[i] = calloc(sizeof(long long), 2);
		scanf("%lld-%lld", &(ranges[i][0]), &(ranges[i][1]));
	}

	return ranges;
}

bool is_fresh_ingredient(long long id, long long **ranges, int range_count){
	int i;

	for(i = 0; i < range_count; i++){
		if(ranges[i][0] <= id && id <= ranges[i][1]){
			return true;
		}
	}

	return false;
}

void solve(){
	int i, range_count, fresh_id_count;
	scanf("%d", &range_count);
	long long id, **ranges = read_ranges(range_count);

	fresh_id_count = 0;
	while(scanf("%lld", &id) != EOF){
		if(is_fresh_ingredient(id, ranges, range_count)){
			fresh_id_count++;
		}
	}
	
	for(i = 0; i < range_count; i++) free(ranges[i]);
	free(ranges);

	printf("%d\n", fresh_id_count);
}

int main(){
	solve();

	return 0;
}
