/**
 *	author: levimigom
 *	created: 2025-12-05 12:02:03
 **/
#include <stdio.h>
#include <stdlib.h>
#define ll long long

ll **read_ranges(int range_count){
	int i;	
	ll **ranges = calloc(sizeof(ll*), range_count);

	for(i = 0; i < range_count; i++){
		ranges[i] = calloc(sizeof(ll), 2);
		scanf("%lld-%lld", &(ranges[i][0]), &(ranges[i][1]));
	}

	return ranges;
}

static int cmp_range(const void *p1, const void *p2){
	const ll *range1 = *((const ll**) p1);
	const ll *range2 = *((const ll**) p2);

	if(range1[0] < range2[0] || (range1[0] == range2[0] && range1[1] < range2[1])){
		return -1;
	} else if(range1[0] == range2[0] && range1[1] == range2[1]){
		return 0;
	} else {
		return 1;
	}
}

ll min(ll a, ll b){ return(a < b ? a : b); }
ll max(ll a, ll b){ return(a < b ? b : a); }

int merge_ranges(ll **ranges, int *range_count){
	int i, j, merged_count;

	merged_count = 0;

	qsort(ranges, *range_count, sizeof(ll*), cmp_range);
	for(i = 0; i < *range_count - 1; i++){
		if(ranges[i + 1][0] <= ranges[i][1]){
			ranges[i][0] = min(ranges[i][0], ranges[i + 1][0]);
			ranges[i][1] = max(ranges[i][1], ranges[i + 1][1]);
			
			free(ranges[i + 1]);
			for(j = i + 1; j < *range_count - 1; j++) ranges[j] = ranges[j + 1];
	
			*range_count -= 1;
			merged_count++;
		}
	}

	return merged_count;
}

void solve(){
	int i, range_count;
	scanf("%d", &range_count);
	ll fresh_ids, **ranges = read_ranges(range_count);

	while(merge_ranges(ranges, &range_count));

	fresh_ids = range_count;
	for(i = 0; i < range_count; i++) fresh_ids += ranges[i][1] - ranges[i][0];

	printf("%lld\n", fresh_ids);

	for(i = 0; i < range_count; i++) free(ranges[i]);
	free(ranges);	 
}

int main(){
	solve();

	return 0;
}
