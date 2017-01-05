#include<bits/stdc++.h>
#define M 99999 
using namespace std;
int T,h[55],l[M],e[M],c[M],v[55],f[55],t,s,O=1<<30,F=1,i,j,n;
void A(int x,int y,int z){e[++t]=y,l[t]=h[x],h[x]=t,c[t]=z;e[++t]=x,l[t]=h[y],h[y]=t,c[t]=0;}
int S(int x,int F)//网络流
{
	if(x==T)return F;
	int r=0,t,i;
	for(i=h[x];i;i=l[i])if(c[i]&&f[x]==f[e[i]]+1)if(t=S(e[i],min(F-r,c[i])),c[i]-=t,c[i^1]+=t,(r+=t)>=F||f[0]>T)return r;
	if(!--v[f[x]])f[0]=T+1;++v[++f[x]];
	return r;
}
#define B for(s=i=0;i<=T;i++)h[i]=v[i]=f[i]=0;t=1;A(0,a1+1,an*2);A(a2+1,T,an*2);A(0,b1+1,bn*2),A(b2+1,T,bn*2);for(i=1;i<=n;i++)for(j=1;j<=n;j++)A(i,j,G[i-1][j-1]=='O'?2:G[i-1][j-1]=='N'?O:0);while(f[0]<T+1)s+=S(0,O);F&=s==2*(an+bn)
class OldBridges
{
	public:
		string isPossible(vector<string> G,int a1,int a2,int an,int b1,int b2,int bn){n=G.size(),T=n+1;B;swap(b1,b2);B;return F?"Yes":"No";}
};
