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

#define N 605
#define M 300
#define seed 23333
#define Mo 998244353

using namespace std;
map<pair<int,int>,int>mp;
int i,j,m,n,p,k,G[N+1][N+1],F[N+1][N+1],R[N+1][N+1];
int SUM(int sx,int sy,int ex,int ey)
{
		int S=G[ex][ey];
		if (sx) S-=G[sx-1][ey];
		if (sy) S-=G[ex][sy-1];
		if (sx&&sy) S+=G[sx-1][sy-1];
		return S; 
}
class DrawingPointsDivOne{
	public:
	int maxSteps(vector <int> x, vector <int> y)
	{
		 n=x.size();
		 for (i=0;i<n;++i) F[M+x[i]][M+y[i]]=1,mp[mk(M+x[i],M+y[i])]=1;
		 for (i=0;i<300;++i) //枚举最后走的步数 
		 {
		 		memset(R,0,sizeof(R));
		 		if (i%2==0) //向外还原 
		 		{
		 			for (j=0;j<N;++j)
		 				for (k=0;k<N;++k)
		 					if (F[j][k])
		 						R[j-1][k-1]=R[j][k-1]=R[j-1][k]=R[j][k]=1;
		 		}
		 		else 
		 		{
				 	for (j=0;j<N;++j)
					 	for (k=0;k<N;++k)
						   if (F[j][k])
						   	  R[j][k]=R[j][k+1]=R[j+1][k+1]=R[j+1][k]=1;						 		
		 		}
		 		memcpy(F,R,sizeof(F));
				for (j=0;j<N;++j) //做前缀和 
					for (k=0;k<N;++k)
					{
						    G[j][k]=F[j][k];
							if (j) G[j][k]+=G[j-1][k];
							if (k) G[j][k]+=G[j][k-1];
							if (j&&k) G[j][k]-=G[j-1][k-1];
					}
				if (i%2==0) //判断每个点存不存在 
				{
						for (j=0;j+i+1<N;++j)
							for (k=0;k+i+1<N;++k)
								if (SUM(j,k,i+j+1,i+k+1)==(i+2)*(i+2))
									if (!mp[mk(j+i/2+1,k+i/2+1)]) return i;
				}
				else 
				{
						for (j=0;j+i+1<N;++j)
							for (k=0;k+i+1<N;++k)
							  if (SUM(j,k,i+j+1,i+k+1)==(i+2)*(i+2))
							  	if (!mp[mk(j+i/2+1,k+i/2+1)]) return i;
				}
		 }
		 return -1;
	}
};
