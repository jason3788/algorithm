
void BFS(int v){
	insert_queue(v);
	state[v]=waiting;
	while(!isempty_queue()){
		v=delete_queue();
		printf("visit %d",v);
		state[v]=visited;
		int i;
		for(i=0;i<n;i++){
			if(G[v][i]==1 && state[i]==initial){
				insert_queue(i);
				state[i]=waiting;
			}
		}
	}
}

void bfs(struct Graph* graph, int start) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // Enqueue the starting node and mark it as visited
    queue[rear++] = start;
    graph->visited[start] = 1;

    while (front < rear) {
        // Dequeue a node from the queue and print it
        int node = queue[front++];
        printf("%d ", node);

        // Add its neighbors to the queue
        struct Node* temp = graph->adjList[node].head;
        while (temp) {
            int neighbor = temp->dest;
            if (!graph->visited[neighbor]) {
                queue[rear++] = neighbor;
                graph->visited[neighbor] = 1;
            }
            temp = temp->next;
        }
    }
}
