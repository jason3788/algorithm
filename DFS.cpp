#include<stdio.h>
int G[10][10],visited[10]={0},n;
void DFS(int i){
	printf("visit %d\n",i);
	visited[i]=1;
	int j;
	for(j=0;j<n;j++){
		if(visited[j]==0 && G[i][j]==1){
			DFS(j);
		}
	}
}

int main(){
	int i,j;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&G[i][j]);
		}
	}
	DFS(3);
}

