#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 1024
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,vis[N][M];
pair<int,int> Q[M*M];
class XorTravelingSalesman{
	public:
		int maxProfit(vector <int> val, vector <string> roads)
		{
				n=val.size();
				int l=1,r=1;
				vis[0][val[0]]=1;
				Q[r=1]=mk(0,0);
				for (;l<=r;++l) //利用bfs来更新每个点的存在性 
				{
						pair<int,int> p=Q[l];
						for (i=0;i<n;++i)
							if (roads[p.fi][i]=='Y')
							{
								if (!vis[i][p.se^val[i]])
								{
									  vis[i][p.se^val[i]]=1;
									  Q[++r]=mk(i,p.se^val[i]);
								}
							}
				}
				for (i=M-1;i>=0;--i)
					for (j=0;j<n;++j)
						if (vis[j][i]) return i;
		}
};

