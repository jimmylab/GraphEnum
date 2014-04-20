#include <iostream>
#include "GraphCollection.h"
/// 求从数组a[1..n]中任选m个元素的所有组合。
/// a[1..n]表示候选集，n为候选集大小，n>=m>0。
/// b[1..M]用来存储当前组合中的元素(这里存储的是元素下标)，
/// 常量M表示满足条件的一个组合中元素的个数，M=m，这两个参数仅用来输出结果。
void combine( int** a, int n, int m,  int* b, const int M,
			 GraphCollection* table, const int maxVert ) {
	for( int i=n; i>=m; i-- ) {    // 注意这里的循环范围
		b[m-1] = i - 1;
		if (m > 1)
			combine( a, i-1, m-1, b, M, table, maxVert );
		else {    // m == 1, 输出一个组合
			Graph temp(maxVert);
			for( int j=M-1; j>=0; j-- )
				temp.SetVertex(a[b[j]]);
			//temp.LineSum(); temp.GetRank();
			table->InsetUnique(temp, M);
		}
	}
}