#include<bits/stdc++.h>
#define T(x) x<58?x-48:x>96?x-87:x-29
#define N 20010
using namespace std;
int T,h[N],l[N],e[N],c[N],v[N],f[N],t=1,O=1<<30,n,m,i,j,s,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},x,y,k,b,g;
void A(int x,int y,int z){e[++t]=y,l[t]=h[x],h[x]=t,c[t]=z,e[++t]=x,l[t]=h[y],h[y]=t;}
int S(int x,int F)//最小割
{
	if(x==T)return F;
	int r=0,t,i;
	for(i=h[x];i;i=l[i])if(c[i]&&f[x]==f[e[i]]+1)if(t=S(e[i],min(F-r,c[i])),c[i]-=t,c[i^1]+=t,(r+=t)>=F||f[0]>T)return r;
	if(!--v[f[x]])f[0]=T+1;++v[++f[x]];
	return r;
}
class SurroundingGame
{
	public:
		int maxScore(vector<string> C,vector<string> B)
		{
			for(n=C.size(),m=C[0].size(),T=n*m*2+1;i<n;i++)for(j=0;j<m;j++)for(s+=b=T(B[i][j]),g=T(C[i][j]),A(i*m+j,i*m+j+n*m,b),i+j&1?A(T-1,i*m+j,g):A(i*m+j+n*m,T,g),k=0;k<4;k++)if(x=i+dx[k],y=j+dy[k],~x&&~y&&x<n&&y<m)i+j&1?A(i*m+j+n*m,x*m+y+n*m,O):A(x*m+y,i*m+j,O);
			while(f[0]<=T)s-=S(T-1,O);
			return s;
		}
};
