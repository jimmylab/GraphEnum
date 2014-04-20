#include "Graph.h"

Graph::Graph(int d) : Matrix<char>( d, d ) , d(d), lineSum(-1) {}
Graph::Graph(Graph& src) : Matrix<char>(src) { d=src.d; lineSum=src.d; }

void Graph::SetVertex( int p[] ) {
	a[p[0]][p[1]] = 1; a[p[1]][p[0]] = 1;
}

std::ostream& operator<<( std::ostream& out, Graph& graph ) {
	int i, j;
	//out<<"©°"; for ( i=0; i<graph.d; i++ ) out<<"  "; out<<" ©´\n";
	for ( i=0; i<graph.d; i++ ) {
		//out<<"©¦";
		for ( j=0; j<graph.d; j++ ) out/*<<' '*/<<(int)graph.a[i][j];
		out<<" ";//out<<" ©¦\n";
	}
	out<<'\n';//out<<"©¸"; for ( i=0; i<graph.d; i++ ) out<<"  "; out<<" ©¼\n";
	return out;
}

int Graph::GetRank() {
	if ( r < 0 ) Matrix<char>::Gaussian();
	return r;
}

long long Graph::LineSum() {
	if ( lineSum >=0 ) return lineSum;
	int *s = new int[d];
	int i, j, t; long long base=1; long long sum=0;
	for ( i=0; i<d; i++ ) {
		s[i] = 0;
		for ( j=0; j<d; j++ ) s[i]+=a[i][j];
	}
	for ( i=0; i<d; i++ ) for ( j=i+1; j<d; j++ ) if (s[i]>s[j]) { t=s[i]; s[i]=s[j]; s[j]=t; }
	for ( i=0; i<d; i++, base*=10 ) sum+=base * s[i];
	lineSum = sum;
	delete[] s;
	return sum;
}

Graph::~Graph() {}
