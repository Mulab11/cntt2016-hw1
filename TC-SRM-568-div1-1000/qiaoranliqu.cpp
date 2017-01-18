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
vector<pair<int,int> >v[N];
int i,j,m,n,p,k,r[N],L[N],R[N],tot,ID[N],A[N],cnt,w[N];
int Q[N];
struct Node{
		int x,y;
}seg[N];
int wow(int x)
{
	 int i,l=1; Q[Q[0]=1]=x; w[x]=0;
	 for (;l<=Q[0];++l)
	 {
	 		int p=Q[l];
	 		for (i=0;i<(int)v[p].size();++i)
	 		{
	 				int k=v[p][i].fi,g=v[p][i].se;
	 				if (w[k]==-1)
	 				{
	 					w[k]=w[p]^g;
	 					Q[++Q[0]]=k;
	 				}
	 				else if (w[k]!=(w[p]^g)) return 0;
	 		}
	 }
	 return 1;
}
int bfs()
{
		memset(w,-1,sizeof(w));
		int i;
		for (i=0;i<=tot;++i)
			if (w[i]==-1)
				if (!wow(i)) return 0;
		return 1;
}
int bfs2()
{
		memset(w,-1,sizeof(w));
		int i;
		if (w[0]==-1) if (!wow(0)) return 0;
		if (w[tot]==-1) if (!wow(tot)) return 0;
		for (i=0;i<=tot;++i)
			if (w[i]==-1)
				if (!wow(i)) return 0;
		return w[0]==w[tot];
}
int check()
{
		int i,j;
		for (i=1;i<=A[0];++i)
		{
			int cnt=0;
			for (j=1;j<=A[0];++j)
				if (ID[i]==ID[j]) ++cnt;
			if (cnt!=2) return 0;
		}
		tot=0;
		for (i=0;i<=n;++i) if (L[i]!=-1) seg[++tot]=(Node){L[i],R[i]};
		for (i=1;i<=A[0];++i)
		{
				for (j=i+1;j<=A[0];++j)
					if (ID[i]==ID[j])
					  seg[++tot]=(Node){A[i],A[j]}; 
		}
		for (i=1;i<=tot;++i) //将每条线段找出来，然后判断每两条线段是否有交,然后做二分图判定即可. 
		{
			v[i].clear();
			for (j=1;j<=tot;++j)
				if (i!=j&&((seg[j].x<seg[i].x&&seg[j].y>seg[i].x&&seg[j].y<seg[i].y)
						||(seg[j].x>seg[i].x&&seg[j].x<seg[i].y&&seg[j].y>seg[i].y))
				   )
				   v[i].pb(mk(j,1));
		}
		return bfs();
}
int dfs(int x,int y)
{
		if (x>A[0]) return check();
		else
		{
				ID[x]=y;
				if (dfs(x+1,y+1)) return 1;
				int i;
				for (i=1;i<y;++i) 
				{
					ID[x]=i;
					if (dfs(x+1,y)) return 1;
				}
				return 0;
		}
}
string baoA()
{
	for (i=1;i<=n;++i) 
	if (r[i]!=-1)
	{
		if (L[r[i]]==-1) L[r[i]]=i; else R[r[i]]=i;
	}
	for (i=1;i<=n;++i) if (r[i]==-1) A[++A[0]]=i;
	if (dfs(1,1)) return "POSSIBLE";
	return "IMPOSSIBLE"; 
}
int sum[N];
int mdzz()
{
		int i;
		for (i=1;i<=A[0];++i)
			for (j=1;j<=A[0];++j)
				if (i!=j&&ID[i]==ID[j])
					if (L[A[i]]<L[A[j]]&&R[A[i]]>L[A[j]]&&R[A[i]]<R[A[j]]) return 0;
		memset(sum,0,sizeof(sum));
		tot=n;
		for (i=0;i<=tot;++i) v[i].clear();
		for (i=1;i<=n;++i) //我们考虑每个弧下面和其同向的点的个数,如果都是偶数的话,那么就存在一组合法解,所以判断一下即可. 
		{
			if (r[i]==-1) 
				sum[i]=sum[i-1]^1;
			else sum[i]=sum[i-1],v[i].pb(mk(i-1,0)),v[i-1].pb(mk(i,0));
		}
		for (i=1;i<=A[0];++i)
			if (ID[i]==1)
			v[R[A[i]]].pb(mk(L[A[i]]-1,sum[R[A[i]]]^sum[L[A[i]]-1])),
			v[L[A[i]]-1].pb(mk(R[A[i]],sum[R[A[i]]]^sum[L[A[i]]-1]));
			else 
			v[R[A[i]]].pb(mk(L[A[i]]-1,0)),
			v[L[A[i]]-1].pb(mk(R[A[i]],0));
		if (bfs2()) return 1;
		return 0;
}
int Dfs(int x)
{
		if (x>A[0]) return mdzz();
		else 
		{
			ID[x]=0;
			if (Dfs(x+1)) return 1;
			ID[x]=1;
			if (Dfs(x+1)) return 1; 
		}
		return 0;
}
string baoB() //当确定的位置较少时,那么不妨枚举每个确定的连线一开始是朝上还是朝下的. 
{
	for (i=1;i<=n;++i)
		if (r[i]!=-1)
		{
				if (L[r[i]]==-1) A[++A[0]]=r[i],L[r[i]]=i; else R[r[i]]=i;
		}
	if (Dfs(1)) return "POSSIBLE";
	return "IMPOSSIBLE";
}
class DisjointSemicircles{
	public:
		string getPossibility(vector <int> labels)
		{
				n=labels.size();
				for (i=1;i<=n;++i) r[i]=labels[i-1],cnt+=(r[i]==-1);
				memset(L,-1,sizeof(L));
				memset(R,-1,sizeof(R)); 
				if (cnt<=12) return baoA(); //当未确定的位置较少时,我们不妨直接暴力枚举匹配的情况,此处复杂度为O(C(cnt,cnt/2)*(cnt/2)!) 
				else return baoB();
		}
}MRT;
