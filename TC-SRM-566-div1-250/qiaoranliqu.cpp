#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,A[N][N];
long long power(long long x,int y)
{
	long long sum=1;
	for (;y;y>>=1)
	{
		if (y&1) sum*=x;
		x*=x;
	}
	return sum;
}
class PenguinSledding{
	public:
		long long countDesigns(int n, vector <int> a, vector <int> b)
		{
			 long long ans=(int)a.size()+1;
			 for (i=0;i<(int)a.size();++i) A[a[i]][b[i]]=A[b[i]][a[i]]=1;
			 for (i=1;i<=n;++i) //枚举以点i为中心,其他点都有边连向j的方案 
			 {
			 		k=0;
			 	 	for (j=1;j<=n;++j) k+=A[i][j];
			 	 	if (k>1)
			 	 	ans+=power(2ll,k)-1-k;
			 }
			 for (i=1;i<=n;++i) //求图中三角形的数量 
			 	for (j=i+1;j<=n;++j)
			 		for (k=j+1;k<=n;++k)
			 				if (A[i][j]&&A[j][k]&&A[k][i]) ++ans;
			 return ans;
		}
}MRT;

int main()
{
	 cout<<MRT.countDesigns(4,{1,2,3},{2,3,4});
}

