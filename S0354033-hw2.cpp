// A union by rank and path compression based program to detect cycle in a graph
#include <stdio.h>
#include <stdlib.h>
 
// a structure to represent an edge in graph
struct Edge
{
    int src, dest;
    float weight;
};
 
// a structure to represent a graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges
    struct Edge* edge;
};
 
struct subset
{
    int parent;
    int rank;
};
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i){                  
        //printf("~~parent[%d] = %d\n",i,subsets[i].parent);    
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    //printf("parent[%d] = %d\n",i,subsets[i].parent);
    return subsets[i].parent;
}
int number;
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    //printf("number = %d",number);
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank){
        int temp = subsets[xroot].parent;
        for(int i=0;i<number;i++)
        {
            if(subsets[i].parent == temp){
                //printf("ysubsets[%d].parent = %d\n",i,yroot);
                subsets[i].parent = yroot;
            }
        }            
        //printf("subsets.parent = %d\n",yroot);
    }
    else if (subsets[xroot].rank > subsets[yroot].rank){
        int temp = subsets[yroot].parent;
        for(int i=0;i<number;i++)
        {
            if(subsets[i].parent == temp)
            {
                //printf("xsubsets[%d].parent = %d\n",i,xroot);
                subsets[i].parent = xroot;
            }
        }
        
    }
 
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        int temp = subsets[yroot].parent;
        for(int i=0;i<number;i++)
        {
            //printf("front = %d\t",subsets[i].parent);
            if(temp == subsets[i].parent){
                //printf("xsubsets[%d].parent = %d\n",i,xroot);
                subsets[i].parent = xroot;
            }
        }        
        //printf("subsets.parent = %d\n",xroot);
        subsets[xroot].rank++;
    }
}
 
// The main function to check whether a given graph contains cycle or not

int isCycle( struct Graph* graph )
{
    int V = graph->V;
    int E = graph->E;
 
    // Allocate memory for creating V sets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Iterate through all edges of graph, find sets of both
    // vertices of every edge, if sets are same, then there is
    // cycle in graph.
    for(int e = 0; e < E; ++e)
    {
        int x = find(subsets, graph->edge[e].src);
        //printf("graph->edge[%d].src = %d\tx = %d\t",e,graph->edge[e].src,x);
        int y = find(subsets, graph->edge[e].dest);
        //printf("graph->edge[%d].dest = %d\ty = %d\n",e,graph->edge[e].dest,y);
 
        if (x == y)
            return 1;
 
        Union(subsets, x, y);
    }
    return 0;
}

struct subset* isSet( struct Graph* graph )
{
    int V = graph->V;
    int E = graph->E;
 
    // Allocate memory for creating V sets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Iterate through all edges of graph, find sets of both
    // vertices of every edge, if sets are same, then there is
    // cycle in graph.
    for(int e = 0; e < E; ++e)
    {
        int x = find(subsets, graph->edge[e].src);
        //printf("graph->edge[%d].src = %d\tx = %d\t",e,graph->edge[e].src,x);
        int y = find(subsets, graph->edge[e].dest);
        //printf("graph->edge[%d].dest = %d\ty = %d\n",e,graph->edge[e].dest,y);
 
        Union(subsets, x, y);
    }
    return subsets;
}

int v1[100],v2[100];
float w[100];
int partition(int ,int);
void quickSort(int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
    	j = partition(l, r);
        quickSort(l, j-1);
        quickSort(j+1, r);
   }
	
}



int partition(int l, int r) {
   int i, j;
   float pivot,t;
   pivot = w[l];
   i = l; j = r+1;
		
   while(1)
   {
		do ++i; while( w[i] <= pivot && i <= r );
   		do --j; while( w[j] > pivot );
   		if( i >= j ) break;
   		t = w[i]; 
		w[i] = w[j]; 
		w[j] = t;
		int temp = v1[i];
		v1[i] = v1[j]; 
		v1[j] = temp;
		temp = v2[i]; 
		v2[i] = v2[j]; 
		v2[j] = temp;
   }
    t = w[l]; 
	w[l] = w[j]; 
	w[j] = t;
	int temp = v1[l]; 
	v1[l] = v1[j]; 
	v1[j] = temp;
	temp = v2[l]; 
	v2[l] = v2[j]; 
	v2[j] = temp;
   
   return j;
}



// Driver program to test above functions
int main()
{
	int count=0;
    FILE *fin;
	fin=fopen("test2.txt", "r");
    fscanf(fin,"%d", &number);
    while(fscanf(fin,"%d %d %f",&v1[count],&v2[count],&w[count])!=EOF)
    {
    	count++;
    }
	/* Let us create following graph
         0
        |  \
        |    \
        1-----2 */
    for(int i=0;i<count;i++){
        v1[i] = v1[i]-1;
        v2[i] = v2[i]-1;
    }
    struct Graph* graph[count];
    quickSort(0,count-1);
    int edg=0;
    for(int z=1;z<=count;z++){
        int V = number, E = edg+1;
        graph[z-1] = createGraph(V, E); 
        int c=0;
 	    for(int i=0;i<z;i++){
            
            if(v1[i]!=-1)
            {                
 		        graph[z-1]->edge[c].src = v1[i];
 		        //printf("v1 = %d\t",v1[i]);
    	        graph[z-1]->edge[c].dest = v2[i];
    	        //printf("v2 = %d\n",v2[i]);
    	        graph[z-1]->edge[c].weight = w[i];
    	        c++;        
            }
        }
        struct subset *subsets = isSet(graph[z-1]);
        /*printf("%d\t",subsets[0].parent);
        printf("%d\t",subsets[1].parent);
        printf("%d\t",subsets[2].parent);
        printf("%d\t",subsets[3].parent);
        printf("%d\t",subsets[4].parent);
        printf("%d\t",subsets[5].parent);          */  
		if (isCycle(graph[z-1]))
        {
            printf("step%d : \n",z);
            for(int k=0;k<c;k++){
                printf("(%d,%d)\t",graph[z-1]->edge[k].src+1,graph[z-1]->edge[k].dest+1);
                printf( "Cost : %0.2f\n", graph[z-1]->edge[k].weight);
            }
            
            printf("set : \n");
            for(int k=0;k<number;k++){
                printf("[");
                for(int p=0;p<number;p++){
                    if(subsets[p].parent==k){
                        printf("%d",p+1);
                    }
                }
                printf("]\t");
            }
            
        	printf( "\nGraph contains cycle\n\n" );        	                        
        	v1[z-1] = -1;
        	v2[z-1] = -1;
        	w[z-1] = -1;
        }
    	else
    	{
            printf("step%d : \n",z);
            for(int k=0;k<c;k++){
                printf("(%d,%d)\t",graph[z-1]->edge[k].src+1,graph[z-1]->edge[k].dest+1);
                printf( "Cost : %0.2f\n", graph[z-1]->edge[k].weight);
            }
            
            printf("set : \n");
            for(int k=0;k<number;k++){
                printf("[");
                for(int p=0;p<number;p++){
                    if(subsets[p].parent==k){
                        printf("%d",p+1);
                    }
                }
                printf("]\t");
            }
            
        	printf( "\nGraph doesn't contain cycle\n\n" );
        	edg++;
        }
    }
    // add edge 0-1
    /*graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
 
    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
 
    // add edge 0-2
    graph->edge[2].src = 0;
    graph->edge[2].dest = 2;
    */
    
    system("pause");
    return 0;
}
