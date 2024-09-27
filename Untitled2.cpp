#include<iostream>
using namespace std;
#define INFINITY 99999
#define max_node 20
FILE *file1 = fopen("output1.txt","w+");
FILE *file2 = fopen("output2.txt","w+");

void print(int d[],int prev[],int arr[],int step,int n,int startnode,int count,FILE *fp){
	fprintf(fp,"step:%d\n",step);
	int i;
	fprintf(fp,"d[v] = [");
	for(i=0;i<n;i++){
		if(d[i]==INFINITY)
			fprintf(fp,"¡Û ");
		else
			fprintf(fp,"%d ",d[i]);
	}
	fprintf(fp,"]\n");
	
	fprintf(fp,"prev[v] = [");
	for(i=0;i<n;i++){
		if(prev[i]==-1)
			fprintf(fp,"X ");
		else if(prev[i]==-2)
			fprintf(fp,"U ");
		else
			fprintf(fp,"%d ",prev[i]);
	}
	fprintf(fp,"]\n");
	
	fprintf(fp,"s={");
	for(i=0;i<count;i++){
		if(i==count-1)
			fprintf(fp,"%d",arr[i]);
		else
			fprintf(fp,"%d ",arr[i]);
	}
	fprintf(fp,"}\n\n");
}

void dijsktra(int G[max_node][max_node],int n,int startnode,FILE *fp){
	int d[max_node],prev[max_node],visited[max_node]={},i,j,sum=0,arr[max_node]={};
	
	for(i=0;i<n;i++){
		if(i==startnode){
			d[i]=0;
			prev[i]=-1;
		}
		else{
			d[i]=INFINITY;
			prev[i]=-2;
		}
	}
	print(d,prev,arr,0,n,startnode,sum,fp);
	
	
	for(i=0;i<n;i++){
		d[i]=G[startnode][i];
		if(G[startnode][i]!=0 && G[startnode][i]!=INFINITY)
			prev[i]=startnode;
	}
	visited[startnode]=1;
	arr[sum]=startnode;
	sum++;
	print(d,prev,arr,1,n,startnode,sum,fp);
	
	int count=1;
	while(count<=n-1){
		int min_dis=INFINITY,next;
		for(i=0;i<n;i++){
			if(d[i]<min_dis && visited[i]==0){
				min_dis=d[i];
				next=i;
			}
		}
		visited[next]=1;
		arr[sum]=next;
		sum++;
		for(i=0;i<n;i++){
			if(visited[i]==0){
				if(min_dis+G[next][i]<d[i]){
					d[i]=min_dis+G[next][i];
					prev[i]=next;
				}
			}	
		}
		count++;
		print(d,prev,arr,count,n,startnode,sum,fp);
	}
}


int main(){
	int graph1[max_node][max_node] = {
        {0,     1    , 5    , 7    , 4    , 99999, 99999, 99999, 99999}, 
        {99999, 0,     99999, 99999, 99999, 3    , 10   , 99999, 99999}, 
        {99999, 99999, 0,     99999, 99999, 2    , 99999, 2    , 99999}, 
        {99999, 99999, 99999, 0,     99999, 99999, 1    , 99999, 99999}, 
        {99999, 99999, 99999, 99999, 0,     99999, 99999, 3    , 99999}, 
        {99999, 99999, 99999, 99999, 99999, 0,     99999, 99999, 2    }, 
        {99999, 99999, 99999, 99999, 99999, 99999, 0,     99999, 9    }, 
        {99999, 99999, 99999, 99999, 99999, 99999, 99999, 0    , 5    }, 
        {99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 0    } 
    };
    
    int graph2[max_node][max_node] = {
        {0, 20 , 15 , 99999 , 99999 , 99999}, 
        {2 , 0 , 99999 , 99999 , 10 , 30}, 
        {99999 , 99999 , 0 , 4 , 99999 , 10}, 
        {99999 , 99999 , 99999 , 0 , 99999 , 99999}, 
        {99999 , 99999 , 99999 , 15 , 0 , 99999}, 
        {99999 , 99999 , 99999 , 4 , 10 , 0}
    };
    
	dijsktra(graph1, 9, 0,file1);
	dijsktra(graph2, 6, 0,file2);
	return 0;
}
