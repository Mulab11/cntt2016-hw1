#include<bits/stdc++.h>
#define N 30003
using namespace std;
int T,h[N],l[N],e[N],c[N],v[N],f[N],t=1,O=1<<30,s,i,j,k,tx,ty,n,m,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void A(int x,int y){e[++t]=y,l[t]=h[x],h[x]=t,c[t]=1;e[++t]=x,l[t]=h[y],h[y]=t;}
int S(int x,int F)
{
	if(x==T)return F;
	int r=0,t,i;
	for(i=h[x];i;i=l[i])if(c[i]&&f[x]==f[e[i]]+1)if(t=S(e[i],min(F-r,c[i])),c[i]-=t,c[i^1]+=t,(r+=t)>=F||f[0]>T)return r;
	if(!--v[f[x]])f[0]=T+1;++v[++f[x]];
	return r;
}
int C(int x,int y){return(x+y)%2?2*(y%2):1;}
class TheTilesDivOne
{
	public:
		int find(vector<string> a)
		{
			for(n=a.size(),m=a[0].size(),T=2*n*m+2;i<n;i++)for(j=0;j<m;j++)
			{
				if(a[i][j]=='.')A(i*m+j,i*m+j+n*m);
				if(C(i,j)>1)A(T-1,i*m+j);
				if(!C(i,j))A(i*m+j+n*m,T);
				for(k=0;k<4;k++)if(tx=i+dx[k],ty=j+dy[k],~tx&&~ty&&tx<n&&ty<m&&C(i,j)==C(tx,ty)+1)A(i*m+j+n*m,tx*m+ty);
			}
			while(f[0]<=T)s+=S(T-1,O);
			return s;
		}
};
