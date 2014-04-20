#ifndef _GraphCollection
#define _GraphCollection
#include "Graph.h"

class GraphCollection {
public:
	GraphCollection();
	bool InsetUnique( Graph& g, int vertexNum );
	//void Output();
	~GraphCollection();

private:
	GraphCollection* next;

	Graph* graph;
	//int vertexNum;
	long long exp;
	int rank;
};

#endif // !_GraphCollection
