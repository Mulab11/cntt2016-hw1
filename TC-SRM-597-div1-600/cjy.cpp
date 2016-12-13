#include<bits/stdc++.h>
#define N 200005
using namespace std;
int M[N],m[N],X[N],Y[N],i,j,n,k,K=100000;
int D(long long x,int y){return(int)floor(1.*x/y);}
class ConvexPolygonGame
{
	public:
		string winner(vector<int>x,vector<int>y)//结论：胜利条件只与第一步能否操作有关		
		{
			n=x.size();x.push_back(x[0]);y.push_back(y[0]);
			for(i=0;i<n;i++)if(x[i]==x[i+1])m[x[i]+K]=min(y[i],y[i+1])+1,M[x[i]+K]=max(y[i],y[i+1]);
			else if(x[i]>x[i+1])for(j=x[i];j>=x[i+1];j--)M[j+K]=D(1ll*y[i]*(x[i+1]-j)+1ll*y[i+1]*(j-x[i]),x[i+1]-x[i])+(j!=x[i]&&j!=x[i+1]);
			else for(j=x[i];j<=x[i+1];j++)m[j+K]=D(1ll*y[i]*(x[i+1]-j)+1ll*y[i+1]*(j-x[i])+x[i+1]-x[i]-1,x[i+1]-x[i])+(j==x[i]||j==x[i+1]);
			for(i=0;i<N;i++)for(j=m[i];j<M[i];j++)if(X[++k]=i,Y[k]=j,k>N-4)return"Masha";
			for(i=3;i<=k;i++)if(1ll*(X[i]-X[1])*(Y[2]-Y[1])!=1ll*(X[2]-X[1])*(Y[i]-Y[1]))return"Masha";
			return"Petya";
		}
};
