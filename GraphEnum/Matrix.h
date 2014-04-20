#ifndef _Matrix
#define _Matrix
#include <iostream>
#include <iomanip>

template <typename T>
class Matrix {
public:
	int r;
	Matrix( int m, int n );
	Matrix( Matrix<T>& );
	inline T* operator[]( int index );
	friend std::ostream& operator<<( std::ostream&, Matrix<T>& );
	void Gaussian();
	void Clear();
	~Matrix();

protected:
	T** a;
	int m, n;

};

template <class T, class R>
R** arrayCopy( R** dest, T** src, int m, int n ) {
	int i, j; R* t = new R[(m*n)];
	if ( dest == NULL ) { dest = new R*[m]; for ( i=0; i<m; i++ ) dest[i] = t + (i*n); }
	if ( src != NULL ) {
		for ( i=0; i<m; i++ ) { for ( j=0; j<n; j++ ) dest[i][j] = (R)(src[i][j]); }
	} else {
		for ( i=0; i<m; i++ ) { for ( j=0; j<n; j++ ) dest[i][j] = (R)0; }
	} return dest;
}



template <typename T>
Matrix<T>::Matrix( int m, int n ) : r(-1) {
	this->m = m; this->n=n;
	a = arrayCopy( (T**)NULL, (T**)NULL, m, n );
}

template <typename T>
Matrix<T>::Matrix( Matrix<T>& src ) {
	n=src.n; m = src.m;
	a = arrayCopy( (T**)NULL, src.a, m, n );
	r = src.r;
}

template <typename T>
inline T* Matrix<T>::operator[]( int index ) { return a[index]; }

template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& matrix) {
	int i, j;
	out<<"©°"; for ( i=0; i<matrix.n; i++ ) out<<"           "; out<<"©´\n";
	for ( i=0; i<matrix.m; i++ ) {
		out<<"©¦";
		for ( j=0; j<matrix.n; j++ ) out<<' '<<std::setw(9)<<(double)matrix.a[i][j]<<' ';
		out<<"©¦\n";
	}
	out<<"©¸"; for ( i=0; i<matrix.n; i++ ) out<<"           "; out<<"©¼\n";
	return out;
}

template <typename T>
void Matrix<T>::Gaussian() {
	int i=0, j=0; double t;
	double **A = arrayCopy( (double**)NULL, a, m, n );
	while ( i<m && j<n ) {
		int pivot, k, u;
		for ( pivot = i, k=i+1; k<m; k++ ) 
			if ( abs(A[k][j]) > abs(A[pivot][j]) ) pivot = k;
		if ( abs(A[pivot][j]) > 1e-12 ) {
			for ( k=j; k<n; k++ ) { t=A[pivot][k]; A[pivot][k]=A[i][k]; A[i][k] = t; }
			for ( k=j+1; k<n; k++ ) { A[i][k]/=A[i][j]; } A[i][j] = 1;
			for ( u=i+1; u<m; u++ ) {
				if ( A[u][j] != 0 ) {
					for ( k=j+1; k<n; k++ ) A[u][k] -= A[i][k] * A[u][j];
				} A[u][j] = 0;
			} i++;
		} j++;
	}
	for ( r=m+1, i=m-1; i>=0; i--, r-- ) {
		for ( j=n; j>=0; j-- ) {
			if ( abs(A[i][j]) > 1e-12 ) i = j =-1;
		}
	}
	delete[] A[0]; delete[] A;
}

template <typename T>
Matrix<T>::~Matrix() {
	delete[] (a[0]);
	delete[] a;
}

template <typename T>
void Matrix<T>::Clear() {
	int i, j; for ( i=0; i<m; i++ ) {
		for ( j=0; j<n; j++ ) a[i][j] = 0;
	} r = -1;
}

#endif // !_Matrix