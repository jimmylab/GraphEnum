#include "GraphCollection.h"
#include <iostream>

GraphCollection::GraphCollection() : graph(NULL), next(NULL) {}

bool GraphCollection::InsetUnique( Graph& g, int vertexNum ) {
	if ( graph==NULL ) {
		//graph = new Graph(g);
		graph++;
		exp = g.LineSum(); rank = g.GetRank();
		//this->vertexNum = vertexNum;
		std::cout << vertexNum << ',' << exp << ',' << rank << '|' << g;
		return true;
	} else if ( exp != g.LineSum() || rank != g.GetRank() /*|| vertexNum != this->vertexNum*/ ) {
		if ( next == NULL ) {
			next = new GraphCollection();
			return next->InsetUnique(g, vertexNum);
		}
		if ( next != NULL ) return next->InsetUnique( g, vertexNum );
	} return false;
}

/*void GraphCollection::Output() {
	if ( graph==NULL ) return;
	std::cout << vertexNum << ',' << exp << ',' << rank << '|' << *graph;
	if ( next != NULL ) next->Output();
}*/

GraphCollection::~GraphCollection() {
	if ( next != NULL ) delete next;
	//if ( graph != NULL ) delete graph;
}
