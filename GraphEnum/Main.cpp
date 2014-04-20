#include "Combine.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#include <cstdlib>
#endif // _DEBUG

int main( int argc, char* argv[] ) {
	if (argc < 2) return -1;
	int N = atoi(argv[1]); if ( N<1 && N>18 ) return -2;
	int C = N*(N-1)/2; int i, j, k;

	/* Initial Conditions */
	if ( N >= 2 ) {
		Graph g(N);
		/* 0 Edge (N>=2) */
		cout<<"0 0 0|";
		cout<<g<<endl;
		if ( N <= 2 ) return 0;

		/* 1 Edge (N>=3) */
		int Va[2]={ 0, 1 };
		g.SetVertex(Va);
		cout<<"1 11"; for ( i=N-2; i>0; i-- ) cout<<'0'; cout<<" 2|";
		cout<<g<<endl;
		if ( N <= 3 ) return 0;

		/* 2 Edge (N>=4) */
		int Vb[2] = { 0, 2 }, Vc[2] = { 2, 3 };
		g.SetVertex(Vb);
		cout<<"2 211"; for ( i=N-3; i>0; i-- ) cout<<'0'; cout<<" 2|";
		cout<<g; g.Clear();

		g.SetVertex(Va); g.SetVertex(Vc);
		cout<<"2 1111"; for ( i=N-4; i>0; i-- ) cout<<'0'; cout<<" 4|";
		cout<<g<<endl;
	}

	int *b = new int[C/2];
	int **a = new int*[C];
	for ( i=1, k=0; i<N; i++ ) {
		for ( j=i; j<N; j++, k++ ) {
			a[k] = new int[2];
			a[k][0] = i; a[k][1] = j;
		}
	}
	for ( i=0, k=0; i<N; i++ ) {
		for ( j=i+1; j<N; j++,k++ ) { a[k][0] = i; a[k][1] = j; }
	}

	for ( i=3; i<=C/2; i++ ) {
		GraphCollection* Table = new GraphCollection();
		combine( a, C, i, b, i, Table, N );
		delete Table;
		cout<<endl;
	}

	delete[] b;
	for ( i=0; i<C; i++ ) delete a[i];
	delete[] a;

	#ifdef _DEBUG
	system("pause");
	#endif // _DEBUG
	return 0;
}