#include<bits/stdc++.h>
#define L long long
#define A(a,b,c,e) d[a][b][N+(c)]=min(d[a][b][N+(c)],(L)e)
#define V vector<int>
using namespace std;int N=55,i,j,k,u,v;L O=1ll<<60,l,r=O,d[55][55][110];
class YamanoteLine
{
	public:
		L howMany(L n,V s1,V t1,V l1,V s2,V t2,V l2)
		{
			for(memset(d,0x3f,sizeof(d));i<=n;i++)if(d[i][i][N]=0,i<n)A(i+1,i,0,-1);
			for(A(0,n,1,0),A(n,0,-1,0),i=0;i<s1.size();i++)A(t1[i],s1[i],s1[i]>t1[i],-l1[i]);
			for(i=0;i<s2.size();i++)A(s2[i],t2[i],-(s2[i]>t2[i]),l2[i]);
			for(k=0;k<=n;k++)for(i=0;i<=n;i++)for(u=0;u<2*N;u++)if(d[i][k][u]<O)for(j=0;j<=n;j++)for(v=max(0,N-u);v<min(2*N,3*N-u);v++)d[i][j][u+v-N]=min(d[i][j][u+v-N],d[i][k][u]+d[k][j][v]);
			for(i=0;i<=n;i++)
			{
				if(d[i][i][N]<0)return 0;
				for(j=0;j<N;j++)if(d[i][i][j]<O)r=min(r,d[i][i][j]/(N-j));
				for(j=N+1;j<N+N;j++)l=max(l,(-d[i][i][j]-1)/(j-N)+1);
			}
			return r==O?-1:max(r-l+1,(L)0);
		}
};
