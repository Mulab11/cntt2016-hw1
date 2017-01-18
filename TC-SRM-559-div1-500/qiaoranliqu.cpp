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

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,vis[N],size[N],deep[N],full[N],flag,MD[N],lim;
long long ans,Ans[N],fac[N];
vector<int>v[N];
void add(int x,int y)
{
	 v[x].pb(y); v[y].pb(x);
}
void dfs(int x)
{
		size[deep[x]]++;
		vis[x]=1; 
		int i;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (vis[p]) continue;
				deep[p]=deep[x]+1;
				dfs(p);
		}
}
inline bool cmp(int a,int b)
{
	 return MD[a]>MD[b];
}
void work(int x)
{
		int f=0,i,A[N]={0};
		vis[x]=1; MD[x]=deep[x];
		for (i=0;i<(int)v[x].size();++i)  
		{
				int p=v[x][i];
				if (vis[p]) continue;
				work(p);
				MD[x]=max(MD[x],MD[p]); //记录最深的深度 
				f=1;
				A[++A[0]]=p;
		}
		if (!f) //用FULL表示这个节点下面是否为一颗满二叉树 
		{
			 if (MD[x]==lim) full[x]=2; 
			 else full[x]=0;
			 Ans[x]=1;
		}
		else 
		{	
			  Ans[x]=1;
			  sort(A+1,A+A[0]+1,cmp);
			  if (A[0]>2) flag=0; //一个点至多只能有2个儿子 
			  int AA=0,BB=0,CC=0;
			  for (i=1;i<=A[0];++i) //记录每个儿子在最深一层的情况,AA表示满的,BB表示有一部分,CC表示空的 
			  {
			  	if (full[A[i]]==2) ++AA;
				if (full[A[i]]==1) ++BB;
				if (full[A[i]]==0) ++CC;
				Ans[x]*=Ans[A[i]];	  
			  }
			  if (BB>1) flag=0;
			  if (!AA&&!BB) full[x]=0; //更新本节点的情况 
			  else if (!BB&&!CC) full[x]=2;
			  else full[x]=1; 
			  if (A[0]==1&&full[x]==2) full[x]=1; //如果只有一个儿子该节点也是不满的. 
			  Ans[x]*=fac[AA]*fac[CC];
		}
}
class HatRack{
	public:
		long long countWays(vector <int> knob1, vector <int> knob2)
		{
			  n=(int)knob1.size()+1;
			  for (i=0;i<n-1;++i)	add(knob1[i]-1,knob2[i]-1);
			  for (i=1,fac[0]=1;i<N;++i) fac[i]=fac[i-1]*i;
			  for (i=0;i<n;++i) //枚举一个点作为根 
			  {
			  		memset(vis,0,sizeof(vis));
			  		memset(size,0,sizeof(size));
			  		memset(deep,0,sizeof(deep));
			  		dfs(i);
			  		for (j=n;j>=0;--j) if (size[j]) break;
			  		lim=j;
					for (--j;j>=0;--j) if (size[j]!=(1ll<<j)) break; //先判断每层的size对不对 
					if (j>=0) continue;
					memset(vis,0,sizeof(vis));
					memset(full,0,sizeof(full));
					memset(Ans,0,sizeof(Ans)); flag=1; 
					work(i);  //计算答案 
					ans+=flag*Ans[i];
			  }
			  return ans;
		}
}G;

int main()
{
	 cout<<G.countWays({1,1,2,2,11,11,8,8,3,3,4,4,5},{2,3,11,8,12,13,9,10,4,5,7,6,14});
}
