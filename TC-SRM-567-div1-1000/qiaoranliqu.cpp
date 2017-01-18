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
#define Mo 1000000009

using namespace std;
int i,j,m,n,p,k,W,h[N],vis[N][N];
map<pair<int,vector<int> >,int>mp;
void jia(int &x,int y)
{
		x+=y; if (x>=Mo) x-=Mo;
}
int dfs(int x,vector<int> v) //可以证明,在本题中,状态数至多为2^W,搜索足以通过本题. 
{
	if (x==-1) return 1;
	if (mp.find(mk(x,v))!=mp.end()) return mp[mk(x,v)];
	int sum=0,i,j;
	vector<int>vec;
	i=x;
				for (j=0;j<W;++j) //暴力枚举这座山放的位置 
				{
					vec.clear();
					for (k=0;k<W;++k) vec.pb(v[k]);
					for (k=0;k<W;++k) //通过计算高度来判断是否合法. 
					{
							int hh=h[i]-abs(j-k);
							if ((vis[i][k]&&hh<=vec[k])||(!vis[i][k]&&hh>vec[k])) break;
							vec[k]=max(hh,vec[k]);
					}
					if (k!=W) continue;
					jia(sum,dfs(x-1,vec));
				}
	return mp[mk(x,v)]=sum;
}
class Mountains{
	public:
		int countPlacements(vector <int> heights, vector <string> visibility)
		{
			n=heights.size();
			for (i=0;i<n;++i) h[i]=heights[i];
			W=visibility[0].length();
			for (i=0;i<n;++i)
			  for (j=0;j<W;++j) vis[i][j]=visibility[i][j]=='X';
			vector<int> v;
			for (i=0;i<W;++i) v.pb(0); //初始状态中均为未知. 
			return dfs(n-1,v);
		}
}MRT;

int main()
{
	cout<<MRT.countPlacements({2, 3, 2},{"------","XXXX--","---XXX"});
}
