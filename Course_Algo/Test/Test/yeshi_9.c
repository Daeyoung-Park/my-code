/*
	Graph�� �ٷ�� ���� ����� �ڵ� �����̿���.

	��:
		- ���� algorithm���� ���� ���ϰ� ������ �� �ֵ��� �ۼ� / ���� ������ ���� �ڵ带 ������ �ξ����.
		- �ۼ� ���Ǹ� ���� typedef�� ���� �־� �ξ����.
*/


#include <stdio.h>
#include <stdlib.h>

/*
	Vertex ����
*/

// TODO: ������ Ư¡�� ���� �� vertex���� � ���� ���� �� �ľ��Ͽ� ������ ��� ���� ����
#define V_WHITE 0
#define V_GRAY  1
#define V_BLACK 2

struct Vertex_t // ���׶�� �ϳ���
{
	int state;
	int distance;
	int idx_v_from;
};

typedef struct Vertex_t V;

// TODO: Vertex ����ü�� ������ ���� ������ ���� �̸� ��� �ε��� �����ϱ�
void Init_Vertex(V *vertexToInitialize)
{
	vertexToInitialize->state = V_WHITE;
	vertexToInitialize->distance = 0x7FFFFFFF;
	vertexToInitialize->idx_v_from = -1;
}


/*
	Edge ����
*/

// TODO: ������ Ư¡�� ���� �� edge���� � ���� ���� �� �ľ��Ͽ� ����ü �������� ����ų� �׳� int ���� ����
//       (��� 'edge ����' ������ ��Ÿ���� �ϹǷ� int �� �ϳ� ������ �ʿ��� �ſ���)
//#define USE_STRUCTURED_EDGE // ���ϻ���ҵ�

#ifdef USE_STRUCTURED_EDGE
struct Edge_t
{
	int weight;
};

typedef struct Edge_t E;
#else

typedef int E;

#endif

// TODO: Edge ������ ���� ������ ���� �̸� ��� �ε��� �����ϱ�
void Init_Edge(E *edgeToInitialize)
{
	*edgeToInitialize = 0;
}





/*
	Graph ����

	��:
		- Graph�� �����ϴ� vertex ���� �� �����Ǿ� �ִٰ� �����ϰ� �־��. (ó�� ���� �� ����)
		- Edge ���� �߰��� �ϰ� ���Ŵ� �� �� ���̶�� �����ϰ� �־��.
			> �ߺ��� edge �߰��� ���ؼ��� Ư���� �˻����� ���� �����̿���.
		- ���� graph�� Undirected graph�� �� edge �ϳ��� ���� ������ �� �� ���ܿ�. (������ ������ �Ἥ ���� '����'�ϰ� ������ ����)
			> Vertex�� ��� ���� ���� ���������, edge�� ��� ���� �����ϴ� ���� ���� �����.
		- ��� vertex�� 0������ ������� ��ȣ�� ���´ٰ� �����ϰ� �־��.
*/

#define USE_ADJACENCY_LIST

#ifdef USE_ADJACENCY_LIST
// Adjacency list�� ������ ���� ����� node ����ü����.
struct E_node_t
{
	E e;
	int idx_v_to; // ������
	struct E_node_t *next; 
};

typedef struct E_node_t E_node;
#endif

struct Graph_t
{
	int n_V;

	V *v;

#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *e;
#else
	// Adjacency matrix
	E **e;
#endif
};

typedef struct Graph_t G;



/*
	Graph ��ü�� ���� manipulation�� ���� �Լ���
*/

// �־��� ����ŭ�� vertex�� ���� �� graph�� ����ϴ�.
// (Edge�� ���߿� Add_Edge() �Ἥ �߰��ؾ� ��!)
G *New_Graph(int n_V) // ������ ���� �Լ�
{
	int idx;
	int idx_col;

	G *result = malloc(sizeof(G));

	result->n_V = n_V;
	result->v = malloc(sizeof(V) * n_V);

	for (idx = 0; idx < n_V; ++idx)
		Init_Vertex(&result->v[idx]);


#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	
	result->e = malloc(sizeof(E_node) * n_V);

	for (idx = 0; idx < n_V; ++idx)
		result->e[idx].next = NULL;

#else
	// Adjacency matrix
	result->e = malloc(sizeof(E*)*n_V + sizeof(E)*n_V*n_V);

	for (idx = 0; idx < n_V; ++idx)
	{
		result->e[idx] = &((E*)result->e[n_V])[idx*n_V]; //��� �Ф�
		
		for (idx_col = 0; idx_col < n_V; ++idx_col)
			Init_Edge(&result->e[idx][idx_col]);
	}
#endif
}

// ����� ���� graph�� �����մϴ�.
void Delete_Graph(G *g)
{

#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	int idx_v;
	E_node *ptr;
	E_node *ptr_next;

	for(idx_v=0; idx_v<g->n_V; ++idx_v)
		for(ptr = g->e[idx_v].next; ptr != 0;)
		{
			ptr_next = ptr->next;
			free(ptr);
			ptr = ptr_next;
		}

	free(g->e);
#else
	// Adjacency matrix
	free(g->e);
#endif

	free(g->v);
	free(g);
}

// �ڷᱸ���μ��� �׷������� �����ؾ� �ϴ� operation

// Graph�� �� directed edge�� �߰��մϴ�.
// ���� graph�� undirected graph��� �׳� �̰� �� �� ȣ���ϸ� �� �� �ؿ�.
void Add_Edge(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *newNode;
	E_node *ptr_nodeToAdd;

	newNode = malloc(sizeof(E_node));
	newNode->next = 0;
	newNode->idx_v_to = idx_v_to;
	Init_Edge(&newNode->e);

	for (ptr_nodeToAdd = &g->e[idx_v_from]; ptr_nodeToAdd->next != 0; ptr_nodeToAdd = ptr_nodeToAdd->next);

	ptr_nodeToAdd->next = newNode;

#else
	// Adjacency matrix
	g->e[idx_v_from][idx_v_to] = 1;

#endif
}


// v[from] -> v[to] edge�� �����ϴ��� ���θ� return�մϴ�.
int Adjacent(G *g, int idx_v_from, int idx_v_to)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;

	for (ptr = g->e[idx_v_from].next; ptr != 0; ptr = ptr->next)
		if (ptr->idx_v_to == idx_v_to)
			return 1;

	return 0;
#else
	// Adjacency matrix
	return g->e[idx_v_from][idx_v_to] != 0;
#endif
}

// v[from] -> v[to] edge�� �����ϴ� ��� v[to]���� ���� return�մϴ�.
// ������ �Ʒ��� �ִ� Neighbors()�� ȣ���ϱ� ���� ������ �޸� ĭ�� ��� �α� ���� ȣ��� �ſ���.
int Count_Neighbors(G *g, int idx_v_source)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;
	int count = 0;

	for (ptr = g->e[idx_v_source].next; ptr != 0; ptr = ptr->next)
		++count;

	return count;
#else
	// Adjacency matrix
	int idx_v_target;
	int count = 0;

	for (idx_v_target = 0; idx_v_target < g->n_V; ++idx_v_target)
		if (g->e[idx_v_source][idx_v_target] != 0)
			++count;

	return count;
#endif
}

// v[from] -> v[to] edge�� �����ϴ� ��� v[to]���� 'index'�� out_idxs_v_target ������ Ư���Ǵ� �迭�� ������� ���, �� ���� return�մϴ�.
// ȣ���ڰ� ���� ������ Count_Neighbors()�� ���� ȣ���ؼ� ������ ũ�⸦ ��� �ΰų�,
// �������� �׳� Vĭ¥�� �ϳ� ��� ���� ��Ȱ���ص� �� �� �ؿ�(���� Ƚ���� return���� �����ϸ� ��).
int Neighbors(G *g, int idx_v_source, int *out_idxs_v_target)
{
#ifdef USE_ADJACENCY_LIST
	// Adjacency list
	E_node *ptr;
	int count = 0;

	for (ptr = g->e[idx_v_source].next; ptr != 0; ptr = ptr->next)
	{
		*out_idxs_v_target = ptr->idx_v_to;
		++out_idxs_v_target;
		++count;
	}

	return count;
#else
	// Adjacency matrix
	int idx_v_target;
	int count = 0;

	for(idx_v_target=0; idx_v_target<g->n_V; ++idx_v_target)
		if (g->e[idx_v_source][idx_v_target] != 0)
		{
			*out_idxs_v_target = idx_v_target;
			++out_idxs_v_target;
			++count;
		}

	return count;
#endif
}





/*
	Note.

	���� �� �Ʒ��� main()�� ����� ���� ���α׷� �ڵ带 ������ �� �� �ؿ�.

	���� Graph ���� �Լ��� �� ������ �θ�,
	��а��� �ڵ� ���� �ִ� vertex / edge ������ �ǵ�� ���� ������ Ǯ �� ���� �ſ���!

*/

int main()
{

	return 0;
}