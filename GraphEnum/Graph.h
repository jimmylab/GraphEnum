#ifndef _Graph
#define _Graph
#include "Matrix.h"
//#include <iostream>
class Graph : public Matrix<char> {
public:
	Graph(int);
	Graph(Graph&);
	void SetVertex(int[]);
	friend std::ostream& operator<<( std::ostream&, Graph& );
	int GetRank();
	long long LineSum();
	~Graph();
private:
	int d;
	long long lineSum;
};

#endif // !_GraphMatrix
