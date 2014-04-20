#include <iostream>
#include "GraphCollection.h"
/// �������a[1..n]����ѡm��Ԫ�ص�������ϡ�
/// a[1..n]��ʾ��ѡ����nΪ��ѡ����С��n>=m>0��
/// b[1..M]�����洢��ǰ����е�Ԫ��(����洢����Ԫ���±�)��
/// ����M��ʾ����������һ�������Ԫ�صĸ�����M=m��������������������������
void combine( int** a, int n, int m,  int* b, const int M,
			 GraphCollection* table, const int maxVert ) {
	for( int i=n; i>=m; i-- ) {    // ע�������ѭ����Χ
		b[m-1] = i - 1;
		if (m > 1)
			combine( a, i-1, m-1, b, M, table, maxVert );
		else {    // m == 1, ���һ�����
			Graph temp(maxVert);
			for( int j=M-1; j>=0; j-- )
				temp.SetVertex(a[b[j]]);
			//temp.LineSum(); temp.GetRank();
			table->InsetUnique(temp, M);
		}
	}
}