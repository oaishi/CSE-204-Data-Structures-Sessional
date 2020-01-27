#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define BLACK 3
#define GREY 2

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ;
	int *color;
	int *dist;
	int *parent;
	int *reach;
	int *out;
	int time;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void dfs();
	void dfs(int i); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	color = 0 ;
	dist = 0;
	parent = 0;
	time=0;
	directed = dir ;
	int time;
    int *reach;
    int *out;//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    color = new int[nVertices];
    dist = new int[nVertices];
    parent = new int[nVertices];
    reach = new int[nVertices];
    out = new int[nVertices];

    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    nEdges++;
    if(!directed && u!=v)
    matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices || nEdges ==0) return;
    if(matrix[u][v]==1)
        nEdges--;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if (matrix[u][v] == 1 || matrix[v][u] == 1)
    {
            return true;
    }
    return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices )
        return NULL_VALUE;
    int degree=0;
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i])
            degree++;
    }
    if(directed)
    {
        for(int i=0;i<nVertices , i!= u ;i++)
    {
        if(matrix[i][u])
            degree++;
    }
    }
    return degree;
    //returns the degree of vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0;i<nVertices ;i++)
    {
        if(matrix[u][i] || matrix[i][u])
        {
               if(matrix[v][i] || matrix[i][v])
                return true;
        }
    }
    return false;
}

void Graph::bfs(int source)
{
   for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i]= -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int pop = q.dequeue();
        for(int i =0; i<nVertices; i++)
        {
            if(isEdge(pop,i)&& (color[i]==WHITE || dist[i]>dist[pop]+1))
            {
               parent[i]=pop;
               color[i]=GREY;
               dist[i]=dist[pop]+1;
               q.enqueue(i);
            }
        }
        color[pop]=BLACK;
    }
}

void Graph::dfs(int u)
{
    time++;
    reach[u]=time;
    color[u]=GREY;
    for(int j=0;j<nVertices;j++)
    {
        if(matrix[u][j]==1 && color[j]==WHITE)
        {
            parent[j]=u;
            dist[j]=dist[u]+1;
            dfs(j);
        }
    }
    color[u]=BLACK;
    time++;
    out[u]=time;
}

void Graph::dfs()
{
    //write this function
     for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i]= -1 ;
        dist[i] = INFINITY ;
        reach[i]=-1;
        out[i]=-1;
    }
    dist[0]=0;
    time =0;
    for(int i=0;i<nVertices;i++)
    {
      if(color[i]==WHITE)
            dfs(i);
    }
}

int Graph::getDist(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return dist[v]-dist[u] ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(color) delete[] color; //deallocate memory
    color = 0;
    if(dist) delete[] dist; //deallocate memory
    dist = 0;
    if(parent) delete[] parent; //deallocate memory
    parent = 0;
    if(out) delete[] out; //deallocate memory
    out = 0;
    if(reach) delete[] reach; //deallocate memory
    reach = 0;
    for(int i=0;i<nVertices;i++)
        delete[] matrix[i];
    matrix =0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove edge. \n");
        printf("3. Is a edge. \n");
        printf("4. Get Degree. \n");
        printf("5. Print Graph.\n");
        printf("6. Has Common Adjacent.\n");
        printf("7. Get Distance\n");
        printf("8. BFS.\n");
        printf("9. DFS.\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n" ,g.isEdge(u, v));
        }
        else if(ch==4)
        {
            int u, v;
            scanf("%d", &u);
            v = g.getDegree(u);
            printf("%d\n" ,v);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n" ,g.hasCommonAdjacent(u, v));
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n" ,g.getDist(u, v));
        }
        else if(ch==8)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
        }
        else if(ch==9)
        {
            g.dfs();
        }
        else
        {
            continue;
        }
    }

}
