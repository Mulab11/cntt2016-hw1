#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 10010
using namespace std;
long long a[51],n,m,tot;
long long inf=1e16;
struct ppp
{long long b,c;}b[51];
bool cmp(ppp x,ppp y)
{return x.b<y.b;}
long long to[N],nxt[N],w[N],pre[110],cnt=1;
void ae(int ff,int tt,long long ww)
{
	cnt++;
	to[cnt]=tt;
	nxt[cnt]=pre[ff];
	pre[ff]=cnt;
	w[cnt]=ww;
}
void AE(int ff,int tt,long long ww)
{
	ae(ff,tt,ww);
	ae(tt,ff,0);
}
int s,e;
int d[110],q[110],h,t;
bool bfs()
{
	memset(d,0,sizeof(d));
	h=t=1;d[s]=1;
	q[1]=s;
	int i,j,x,y;
	while(h<=t)
	{
		x=q[h];h++;
		for(i=pre[x];i;i=nxt[i])
		if(w[i])
		{
			j=to[i];
			if(d[j]) continue;
			d[j]=d[x]+1;
			t++;q[t]=j;
		}
	}
	if(d[e]) return true;
	return false;
}
long long dfs(int x,long long v)
{
	if(x==e||v==0) return v;
	long long i,j,ret=0;
	for(i=pre[x];i;i=nxt[i])
	if(w[i])
	{
		j=to[i];
		if(d[j]!=d[x]+1) continue;
		long long f=dfs(j,min(w[i],v));
		v-=f;
		ret+=f;
		w[i]-=f;
		w[i^1]+=f;
		if(!v) break;
	}
	if(!ret) d[x]=-1;
	return ret;
}
long long dinic()
{
	long long ret=0;
	while(bfs())
	ret+=dfs(s,inf);
	return ret;
}
bool check(long long L)
{
	int i,j;
	cnt=1;s=0;e=n+m+1;
	memset(pre,0,sizeof(pre));
	for(i=1;i<=n;i++)
	AE(s,i,L);
	for(i=1;i<=m;i++)
	AE(n+i,e,b[i].c);
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)
	if(a[i]>=b[j].b)
	AE(i,n+j,inf);
	return dinic()==tot;
}
struct SpaceWarDiv1
{
	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount)
	{
		n=magicalGirlStrength.size();
		int i;
		for(i=0;i<n;i++)
		a[i+1]=magicalGirlStrength[i];
		m=enemyStrength.size();
		for(i=0;i<m;i++)
		b[i+1].b=enemyStrength[i],b[i+1].c=enemyCount[i],tot+=enemyCount[i];
		sort(a+1,a+n+1);sort(b+1,b+m+1,cmp);
		if(a[n]<b[m].b) return -1;
		long long l=1,r=inf,mid;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		return l;
	}
};
/*int main()
{
	SpaceWarDiv1 P;
	vector<int> V1,V2;
	vector<long long>V3;
	V1.push_back(2);
	V1.push_back(3);
	V1.push_back(4);
	V2.push_back(1);
	V2.push_back(3);
	V2.push_back(4);
	V3.push_back(2);
	V3.push_back(9);
	V3.push_back(4);
	cout<<P.minimalFatigue(V1,V2,V3);
}*/