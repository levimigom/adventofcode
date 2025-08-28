/**
 *	author: levimigom
 *	created: 2025-08-28 16:58:16
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define STRING_LEN 32

// Declarations
struct Node {
	char id[STRING_LEN];
	struct Edge **edges;
	int edges_size, edges_capacity;
	bool visited;
};

struct Node *node_create(char *id);
void node_add_edge(struct Node *src, struct Node *dst, int distance);
void node_free(struct Node *n);

struct Edge {
	struct Node *dst;
	int distance;
};

struct Edge *edge_create(struct Node *dst, int distance);

struct Graph {
	struct Node **nodes;
	int nodes_size, nodes_capacity;
};

struct Graph *graph_create();
struct Node *graph_get_node(struct Graph *g, char *id);
struct Node *graph_create_node(struct Graph *g, char *id);
struct Node *graph_get_or_create_node(struct Graph *g, char *id);
void graph_add_edge(struct Graph *g, char *src_id, char *dst_id, int distance);
void graph_free(struct Graph *g);

// Definitions
struct Node *node_create(char *id){
	struct Node *n = malloc(sizeof(struct Node));
	strcpy(n->id, id);
	n->edges_size = 0;
	n->edges_capacity = 2;
	n->edges = calloc(sizeof(struct Edge*), n->edges_capacity);
	n->visited = false;
	return n;
}

void node_add_edge(struct Node *src, struct Node *dst, int distance){
	struct Edge *e = edge_create(dst, distance);
	
	if(src->edges_size == src->edges_capacity){
		src->edges_capacity *= 2;
		src->edges = realloc(src->edges, sizeof(struct Edge*) * src->edges_capacity);
	}

	src->edges[src->edges_size++] = e;
}

void node_free(struct Node *n){
	int i;

	for(i = 0; i < n->edges_size; i++){
		free(n->edges[i]);
	}
	free(n->edges);
	free(n);
}

struct Edge *edge_create(struct Node *dst, int distance){
	struct Edge *e = malloc(sizeof(struct Edge));
	e->dst = dst;
	e->distance = distance;
	return e;
}

struct Graph *graph_create(){
	struct Graph *g = malloc(sizeof(struct Graph));
	g->nodes_size = 0;
	g->nodes_capacity = 2;
	g->nodes = calloc(sizeof(struct Node*), g->nodes_capacity);
	return g;
}

struct Node *graph_get_node(struct Graph *g, char *id){
	int i;

	for(i = 0; i < g->nodes_size; i++){
		if(strcmp(g->nodes[i]->id, id) == 0){
			return g->nodes[i];
		}
	}

	return 0;
}

struct Node *graph_create_node(struct Graph *g, char *id){
	struct Node *n = node_create(id);
	
	if(g->nodes_size == g->nodes_capacity){
		g->nodes_capacity *= 2;
		g->nodes = realloc(g->nodes, sizeof(struct Node*) * g->nodes_capacity);
	}

	g->nodes[g->nodes_size++] = n;
	return n;
}

struct Node *graph_get_or_create_node(struct Graph *g, char *id){
	struct Node *n = graph_get_node(g, id);

	if(n == 0){
		return graph_create_node(g, id);
	}

	return n;
}

void graph_add_edge(struct Graph *g, char *src_id, char *dst_id, int distance){
	struct Node *src = graph_get_or_create_node(g, src_id);
	struct Node *dst = graph_get_or_create_node(g, dst_id);

	node_add_edge(src, dst, distance);
	node_add_edge(dst, src, distance);
}

void graph_free(struct Graph *g){
	int i;

	for(i = 0; i < g->nodes_size; i++){
		node_free(g->nodes[i]);
	}
	free(g->nodes);
	free(g);
}

int dfs(struct Node *n){
	n->visited = true;
	
	int i, distance, solution;
	
	solution = -1;
	for(i = 0; i < n->edges_size; i++){
		if(!n->edges[i]->dst->visited){
			distance = n->edges[i]->distance + dfs(n->edges[i]->dst);
			
			if(solution == -1 || solution < distance){
				solution = distance;
			}
		}
	}

	n->visited = false;

	if(solution == -1){
		return 0;
	}
	
	return solution;
}

int max(int a, int b){ return(a < b ? b : a); }

int solve(struct Graph *g){
	int i, solution;

	solution = dfs(g->nodes[0]);
	for(i = 1; i < g->nodes_size; i++){
		solution = max(solution, dfs(g->nodes[i]));
	}

	return solution;
}

int main(){
	struct Graph *g = graph_create();
	char src[STRING_LEN], dst[STRING_LEN];
	int distance;

	while(scanf("%s %*s %s = %d", src, dst, &distance) != EOF){
		graph_add_edge(g, src, dst, distance);
	}

	printf("%d\n", solve(g));
	graph_free(g);

	return 0;
}
