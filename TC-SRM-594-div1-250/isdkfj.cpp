#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
int n,m,f[55][55];
LL a[55],b[55];

int work(){
	f[0][0]=0;
	for(int i=1;i<=n;++i)f[i][0]=0;
	for(int i=1;i<=m;++i)f[0][i]=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		if(a[i]==b[j])f[i][j]=f[i-1][j-1]+1;
		else f[i][j]=max(f[i][j-1],f[i-1][j]);//最长公共子序列 
	return f[n][m];
}

class AstronomicalRecords {
public:
	int minimalPlanets(vector <int> A, vector <int> B) {
		n=A.size();m=B.size();
		int ret=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j){//枚举两个对应的星星 
				for(int k=0;k<n;++k)a[k+1]=LL(A[k])*B[j];
				for(int k=0;k<m;++k)b[k+1]=LL(B[k])*A[i];//按比例放大 
				ret=max(ret,work());
			}
		return n+m-ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
