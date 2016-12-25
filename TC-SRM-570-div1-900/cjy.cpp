#include<bits/stdc++.h>
#define N 9999
using namespace std;
int h[N],e[N],g[N],l[N],w[N],t=1,n,m,T,s[N],S,V[N],d[N],O=1<<30,i,j,s1,s2,t1,t2,t3,c;
void A(int u,int v,int f,int c=0){e[++t]=v;g[t]=h[u];w[t]=f;l[t]=c;h[u]=t;e[++t]=u;g[t]=h[v];l[t]=-c;h[v]=t;}
int W(int u,int f){if(u==T){s1-=f,S+=f*d[T-1];return f;}int i,p=f,t,q;V[u]=1;for(i=h[u];i;i=g[i])if(w[i]&&!V[e[i]])if(t=d[e[i]]+l[i]-d[u],!t){if(q=W(e[i],min(w[i],p)),w[i]-=q,w[i^1]+=q,p-=q,!p)return f;}else s[e[i]]=min(s[e[i]],t);return f-p;}
int C(){int i,t=O;for(i=0;i<=T;i++)if(!V[i])t=min(s[i],t),s[i]=O;for(i=0;i<=T;i++)if(V[i])d[i]+=t;return t!=O;}
class CurvyonRails//分层费用流
{
	public:
		int getmin(vector<string> a)
		{
			for(n=a.size(),m=a[0].size(),T=n*m*3+1;i<n;i++)for(j=0;j<m;j++)if(c=(a[i][j]=='C'),t1=i*m+j,t2=t1+n*m,t3=t2+n*m,a[i][j]!='w')if(i+j&1)s1+=2,A(t1,T,2),A(t2,t1,1),A(t3,t1,1),A(t2,t1,1,c),A(t3,t1,1,c);else
			{
				if(s2+=2,A(T-1,t1,2),A(t1,t2,1),A(t1,t3,1),A(t1,t2,1,c),A(t1,t3,1,c),i)A(t2,t2-m,1);
				if(j)A(t3,t3-1,1);
				if(i<n-1)A(t2,t2+m,1);
				if(j<m-1)A(t3,t3+1,1);
			}
			if(s1!=s2)return -1;
			do{do{memset(V,0,sizeof(V));}while(W(T-1,O));}while(C());
			return s1?-1:S;
		}
};
