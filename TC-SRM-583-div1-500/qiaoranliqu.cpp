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

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans,deg[N],fa[N];
int get(int x)
{
		return fa[x]==x?x:fa[x]=get(fa[x]);
}
void Merge(int x,int  y)
{
		fa[get(x)]=get(y); 
}
class TurnOnLamps{
	public:
	int minimize(vector <int> roads, string initState, string isImportant)
	{
			n=roads.size()+1;
			for (i=0;i<n;++i) fa[i]=i;
			for (i=0;i<n-1;++i)
				if (isImportant[i]=='0') Merge(roads[i],i+1);
			for (i=0;i<n-1;++i) 
			{
					if (initState[i]=='0'&&isImportant[i]=='1') deg[get(i+1)]++,deg[get(roads[i])]++;
			}
			for (i=0;i<n;++i) if (deg[i]&1) ++ans;
			return ans/2; 
	}
};

