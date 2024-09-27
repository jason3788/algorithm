#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	struct node *next;
	int vertex;
}node;

node *G[20];
int visited[20];
int n;

void DFS(int i){
	node *p=G[i];
	printf("visit %d\n",i);
	visited[i]=1;
	while(p!=NULL){
		i=p->vertex;
		if(visited[i]==0){
			DFS(i);
		}
		p=p->next;
	}
}
