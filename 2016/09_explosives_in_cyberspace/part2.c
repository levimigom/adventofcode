#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 32768

struct listnode {
	long multiplier;
	int expiration;
	struct listnode *next;
};

struct listnode* create_node(long multiplier, int expiration){
	struct listnode *node  = malloc(sizeof(struct listnode));
	node->multiplier = multiplier;
	node->expiration = expiration;
	node->next = 0;
	return node;
}

void add_multiplier(struct listnode *root, long multiplier, int expiration){
	while(root->next != 0){
		root = root->next;
	}	

	root->next = create_node(multiplier, expiration);
}

long get_multiplier(struct listnode *root, int index){
	while(root->next != 0 && root->next->expiration <= index){
		struct listnode *next = root->next;
		root->next = root->next->next;
		free(next);	
	}

	if(root->next != 0){
		return get_multiplier(root->next, index) * root->multiplier;
	} else {
		return root->multiplier;
	}	
}

void destroy(struct listnode *node){
	if(node->next != 0){
		destroy(node->next);
	}

	free(node);
}

long calculate_decompressed_length(char *sequence){
	int i, characters, repeat;
	struct listnode *multipliers;
	long length;

	multipliers = create_node(1, LEN);

	length = 0;
	for(i = 0; i < strlen(sequence); i++){
		if('A' <= sequence[i] && sequence[i] <= 'Z'){
			length += get_multiplier(multipliers, i);
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
			
			add_multiplier(multipliers, repeat, i + 1 + characters);
		}
	}

	destroy(multipliers);

	return length;
}

int main(){
	char sequence[LEN];

	scanf("%s", sequence);
	printf("%ld\n", calculate_decompressed_length(sequence));

	return 0;
}
